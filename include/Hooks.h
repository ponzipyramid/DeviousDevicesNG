#pragma once

#include "DeviceManager.h"
#include <detours/detours.h>

namespace DeviousDevices {

    DeviceManager* dManager;

    typedef void(WINAPI* OriginalEquipObject)(RE::ActorEquipManager* a_1, RE::Actor* a_actor,
                                              RE::TESBoundObject* a_object, RE::ExtraDataList* a_extraData,
                                              std::uint32_t a_count, RE::BGSEquipSlot* a_slot,
                                              bool a_queueEquip,
                                              bool a_forceEquip, bool a_playSounds,
                                              bool a_applyNow);
     typedef void(WINAPI* OriginalUnequipObject)(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                                std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                                std::uint64_t a_queueEquip, std::uint64_t a_forceEquip,
                                                std::uint64_t a_playSounds, std::uint64_t a_applyNow,
                                                std::uint64_t a_slotToReplace);
    inline OriginalEquipObject _EquipObject;
    inline OriginalUnequipObject _UnequipObject;

    inline RE::GPtr<RE::InventoryMenu> GetInventoryMenu() {
        auto ui = RE::UI::GetSingleton();
        auto invMenu = ui->GetMenu<RE::InventoryMenu>(RE::InventoryMenu::MENU_NAME);
        return invMenu;
    }
    
    inline void EquipObject(RE::ActorEquipManager* a_1, RE::Actor* actor, RE::TESBoundObject* item,
                            RE::ExtraDataList* a_extraData, std::uint32_t a_count, RE::BGSEquipSlot* a_slot,
                            bool a_queueEquip, bool a_forceEquip, bool a_playSounds,
                            bool a_applyNow) {

        if (dManager->IsInventoryDevice(item) && a_extraData != nullptr) {           
            auto invMenu = GetInventoryMenu();

            if (actor->GetFormID() == 20 && invMenu.get()) {
                dManager->ShowEquipMenu([=](uint32_t result) {
                    if (result == 0) {
                        if (dManager->EquipRenderedDevice(actor, item)) {
                            _EquipObject(RE::ActorEquipManager::GetSingleton(), actor, item, a_extraData, a_count,
                                         a_slot, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow);
                        }
                        
                        invMenu.get()->GetRuntimeData().itemList->Update();
                    }
                });
            }
        } else {
            _EquipObject(a_1, actor, item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds,
                         a_applyNow);
        }            
        
    }
    
    
    inline void UnequipObject(std::uint64_t a_1, RE::Actor* actor, RE::TESBoundObject* item,
                                    std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                    std::uint64_t a_queueEquip, std::uint64_t a_forceEquip,
                                    std::uint64_t a_playSounds, std::uint64_t a_applyNow,
                                    std::uint64_t a_slotToReplace) {
        if (dManager->IsInventoryDevice(item)) {
            SKSE::log::info("unequip devious device detected: {}", item->GetFormID());
            auto invMenu = GetInventoryMenu();
            // if in inventory menu and actor is player
            if (actor->GetFormID() == 20 && invMenu.get()) {
                SKSE::log::info("Player attempting equip from inventory menu");
                // show message box and unequip or don't accordingly
            } else {
                SKSE::log::info("Prevented equip through regular function");
                // prevent equipping on NPCs or player by script
            }
        } else {
            return _UnequipObject(a_1, actor, item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip,
                                  a_playSounds, a_applyNow, a_slotToReplace);
        }
    }

    inline void Install() {
        dManager = &DeviceManager::GetSingleton();

        const auto equipTargetAddress = RE::Offset::ActorEquipManager::EquipObject.address();
        const auto equipFuncAddress = &EquipObject;
        _EquipObject = (OriginalEquipObject)equipTargetAddress;
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)_EquipObject, (PBYTE)&EquipObject);
        if (DetourTransactionCommit() == NO_ERROR)
            logger::info("Installed papyrus hook on EquipObject at {0:x} with replacement from address {0:x}",
                         equipTargetAddress, (void*)equipFuncAddress);
        else
            logger::warn("Failed to install papyrus hook on EquipObject");


        const auto unequipTargetAddress = RE::Offset::ActorEquipManager::UnequipObject.address();
        const auto unequipFuncAddress = &UnequipObject;
        _UnequipObject = (OriginalUnequipObject)unequipTargetAddress;
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)_UnequipObject, (PBYTE)&UnequipObject);
        if (DetourTransactionCommit() == NO_ERROR)
            logger::info(
                "Installed papyrus hook on UnequipObject at {0:x} with replacement from address {0:x}",
                         unequipTargetAddress, (void*)unequipFuncAddress);
        else
            logger::warn("Failed to install papyrus hook on UnequipObject");
    }
} 