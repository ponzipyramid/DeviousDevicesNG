#pragma once

#include "DeviceReader.h"
#include "InventoryFilter.h"
#include <detours/detours.h>
#include "Script.hpp"

namespace DeviousDevices {
    namespace Hooks {
        DeviceReader* g_dManager;

        typedef void(WINAPI* OriginalEquipObject)(  RE::ActorEquipManager* a_1, 
                                                    RE::Actor* a_actor,
                                                    RE::TESBoundObject* a_object, 
                                                    RE::ExtraDataList* a_extraData,
                                                    std::uint32_t a_count, 
                                                    RE::BGSEquipSlot* a_slot, 
                                                    bool a_queueEquip,
                                                    bool a_forceEquip, 
                                                    bool a_playSounds, 
                                                    bool a_applyNow);
        typedef bool(WINAPI* OriginalUnequipObject)(RE::ActorEquipManager* a_1, 
                                                    RE::Actor* a_actor,
                                                    RE::TESBoundObject* a_object,
                                                    std::uint64_t a_extraData, 
                                                    std::uint64_t a_count,
                                                    std::uint64_t a_slot, 
                                                    std::uint64_t a_queueEquip,
                                                    std::uint64_t a_forceEquip, 
                                                    std::uint64_t a_playSounds,
                                                    std::uint64_t a_applyNow, 
                                                    std::uint64_t a_slotToReplace);
        inline OriginalEquipObject   _EquipObject;
        inline OriginalUnequipObject _UnequipObject;

        inline RE::GPtr<RE::InventoryMenu> GetInventoryMenu() {
            auto ui = RE::UI::GetSingleton();
            auto invMenu = ui->GetMenu<RE::InventoryMenu>(RE::InventoryMenu::MENU_NAME);
            return invMenu;
        }

        inline void EquipObject(RE::ActorEquipManager*      a_1,
                                RE::Actor*                  a_actor,
                                RE::TESBoundObject*         a_item,
                                RE::ExtraDataList*          a_extraData,
                                std::uint32_t               a_count,
                                RE::BGSEquipSlot*           a_slot,
                                bool                        a_queueEquip,
                                bool                        a_forceEquip,
                                bool                        a_playSounds,
                                bool                        a_applyNow)
        {

            // Apply inventory filter
            if (InventoryFilter::GetSingleton()->Filter(a_actor,a_item))
            {
                return;
            }

            #if (DD_EQREWORKON == 1U)
            DeviceReader::DeviceUnit* loc_device = g_dManager->GetInventoryDevice(a_item);
            if (loc_device != nullptr) 
            {
                LOG("Handling {} equip", a_item->GetName());
                bool loc_shouldEquipSilently = g_dManager->ShouldEquipSilently(a_actor);
                
                // this is causing issues with DDe
                if (!g_dManager->CanEquipDevice(a_actor, loc_device)) 
                {
                    if (!loc_shouldEquipSilently) RE::DebugNotification("You cannot equip this device");
                    LOG("Failed to equip {}", a_item->GetName());
                    return;
                }

                auto loc_equipDevice = [=](bool equipSilently) {
                    //dManager->EquipRenderedDevice(actor, device);
                    _EquipObject(a_1, a_actor, a_item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip,
                                 a_playSounds, a_applyNow);

                    if (!equipSilently)
                    {
                        g_dManager->ShowManipulateMenu(a_actor, loc_device);
                        if (auto invMenu = GetInventoryMenu().get())
                        {
                            invMenu->GetRuntimeData().itemList->Update();
                        }
                    }
                };

                if (!loc_shouldEquipSilently) 
                {
                    g_dManager->ShowEquipMenu(loc_device, [=](bool equip) {
                        if (equip) loc_equipDevice(loc_shouldEquipSilently);
                    });
                } 
                else 
                {
                    loc_equipDevice(loc_shouldEquipSilently);
                }
            } 
            else 
            #endif
            {
                _EquipObject(a_1, a_actor, a_item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds,
                             a_applyNow);
            }
        }

        inline bool UnequipObject(RE::ActorEquipManager* a_1, RE::Actor* actor, RE::TESBoundObject* item,
                                  std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                  std::uint64_t a_queueEquip, std::uint64_t a_forceEquip, std::uint64_t a_playSounds,
                                  std::uint64_t a_applyNow, std::uint64_t a_slotToReplace) {
            // api calls to remove the device should use the hooked func directly - this is for external attempts

            // cases: remove all items, external mod calling unequip, user trying through inventory

            // need to check for quest item 

            return _UnequipObject(a_1, actor, item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip,
                                  a_playSounds, a_applyNow, a_slotToReplace);
        }

        inline void Install() {
            g_dManager = DeviceReader::GetSingleton();

            const uintptr_t loc_equipTargetAddress = RE::Offset::ActorEquipManager::EquipObject.address();
            _EquipObject = (OriginalEquipObject)loc_equipTargetAddress;

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)_EquipObject, (PBYTE)&EquipObject);

            if (DetourTransactionCommit() == NO_ERROR)
            {
                LOG("Installed papyrus hook on EquipObject at {0:x} with replacement from address {0:x}",
                             loc_equipTargetAddress, (void*)&EquipObject);
            }
            else
            {
                WARN("Failed to install papyrus hook on EquipObject");
            }

            const uintptr_t loc_unequipTargetAddress = RE::Offset::ActorEquipManager::UnequipObject.address();
            _UnequipObject = (OriginalUnequipObject)loc_unequipTargetAddress;

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)_UnequipObject, (PBYTE)&UnequipObject);

            if (DetourTransactionCommit() == NO_ERROR)
            {
                LOG("Installed papyrus hook on UnequipObject at {0:x} with replacement from address {0:x}",
                             loc_unequipTargetAddress, (void*)&UnequipObject);
            }
            else
            {
                WARN("Failed to install papyrus hook on UnequipObject");
            }
        }
    }
} 