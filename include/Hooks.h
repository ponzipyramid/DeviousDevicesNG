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

    inline bool IsInventoryMenuOpen() {
        auto ui = RE::UI::GetSingleton();
        auto mainMenu = ui->GetMenu(RE::InventoryMenu::MENU_NAME);
        return mainMenu.get();
    }
    
    inline void EquipObject(RE::ActorEquipManager* a_1, RE::Actor* actor, RE::TESBoundObject* item,
                            RE::ExtraDataList* a_extraData, std::uint32_t a_count, RE::BGSEquipSlot* a_slot,
                            bool a_queueEquip, bool a_forceEquip, bool a_playSounds,
                            bool a_applyNow) {

        if (dManager->IsInventoryDevice(item) && a_extraData != nullptr) {           
            SKSE::log::info("Equipping device");

            auto ui = RE::UI::GetSingleton();
            auto mainMenu = ui->GetMenu<RE::InventoryMenu>(RE::InventoryMenu::MENU_NAME);

            if (actor->GetFormID() == 20 && mainMenu.get()) {
                dManager->ShowEquipMenu([=](uint32_t result) {
                    SKSE::log::info("Time to actually equip");

                    if (result == 0) {
                        _EquipObject(RE::ActorEquipManager::GetSingleton(), actor, item, a_extraData, a_count, a_slot,
                                     a_queueEquip, a_forceEquip, a_playSounds, a_applyNow);

                        RE::InventoryMenu::RUNTIME_DATA& rData = mainMenu.get()->GetRuntimeData();
                        for (const auto& item : rData.itemList->items) {
                            SKSE::log::info("{} is {}", item->data.GetName(), item->data.GetEquipState());
                        }
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

            // if in inventory menu and actor is player
            if (actor->GetFormID() == 20 && IsInventoryMenuOpen()) {
                SKSE::log::info("Player attempting equip from inventory menu");
                // show message box and equip or don't accordingly
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