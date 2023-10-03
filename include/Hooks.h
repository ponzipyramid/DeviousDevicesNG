#pragma once

#include "DeviceReader.h"
#include "InventoryFilter.h"
#include <detours/detours.h>
#include "Script.hpp"

namespace DeviousDevices {
    namespace Hooks {
        DeviceReader* g_dManager;

        template <class F, class T>
        static void write_vfunc() {
            REL::Relocation<std::uintptr_t> vtbl{F::VTABLE[0]};
            T::func = vtbl.write_vfunc(T::idx, T::thunk);
        }

        struct AddObjectToContainerHook {
            static void thunk(RE::PlayerCharacter* player, RE::TESBoundObject* a_object, RE::ExtraDataList* a_extraList,
                              int32_t a_count, RE::TESObjectREFR* a_fromRefr) {
                if (InventoryFilter::GetSingleton()->TakeFilter(player, a_object)) return;
                func(player, a_object, a_extraList, a_count, a_fromRefr);
            }

            static inline REL::Relocation<decltype(thunk)> func;

            static inline int idx = 0x5A;

            static inline void Install() { write_vfunc<RE::PlayerCharacter, AddObjectToContainerHook>(); }
        };

        struct PickUpObjectHook {
            static void thunk(RE::PlayerCharacter* player, RE::TESObjectREFR* a_item, uint32_t a_count, bool a_arg3,
                              bool a_playSound) {
                if (InventoryFilter::GetSingleton()->TakeFilter(player, a_item->GetBaseObject())) return;
                func(player, a_item, a_count, a_arg3, a_playSound);
            }


            static inline REL::Relocation<decltype(thunk)> func;

            static inline int idx = REL::Module::GetRuntime() != REL::Module::Runtime::VR ? 0xCC : 0xCE;

            static inline void Install() { write_vfunc<RE::PlayerCharacter, PickUpObjectHook>(); }
        };

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
            if (InventoryFilter::GetSingleton()->EquipFilter(a_actor, a_item)) return;

            _EquipObject(a_1, a_actor, a_item, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds,
                         a_applyNow);
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

            AddObjectToContainerHook::Install();
            PickUpObjectHook::Install();

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