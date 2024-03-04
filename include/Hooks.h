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

        struct EquipSpellHook {
            static void thunk(RE::ActorEquipManager* a_manager, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                const RE::BGSEquipSlot& a_slot) {

                if (a_actor && a_object && a_object->Is(RE::FormType::Spell) && 
                    InventoryFilter::GetSingleton()->EquipFilter(a_actor, a_object)) {
                    LOG("EquipSpellHook restricted <{:08X}:{}>", a_object->GetFormID(), a_object->GetName())
                    return;
                }
                return func(a_manager, a_actor, a_object, a_slot);
            }

            static inline REL::Relocation<decltype(thunk)> func;

            static inline void Install() {
                std::array targets_1{std::make_pair(RELOCATION_ID(37939, 38895), REL::VariantOffset(0x47, 0x47, 0x47)),
                                     std::make_pair(RELOCATION_ID(37950, 38906), REL::VariantOffset(0xC5, 0xCA, 0xC5)),
                                     std::make_pair(RELOCATION_ID(37952, 38908), REL::VariantOffset(0xD7, 0xD7, 0xD7))};

                auto& trampoline = SKSE::GetTrampoline();

                for (const auto& [id, offset] : targets_1) {
                    REL::Relocation<std::uintptr_t> target{id, offset};
                    SKSE::AllocTrampoline(14);
                    EquipSpellHook::func = trampoline.write_call<5>(target.address(), EquipSpellHook::thunk);
                }
            }
        };

        struct EquipShoutHook {
            static void thunk(RE::ActorEquipManager* a_manager, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                              RE::BGSEquipSlot* a_slot) {
                // not sure if check for formtype is necessary, don't know if other stuff goes through this function
                if (a_actor && a_object && a_object->Is(RE::FormType::Shout) &&
                    InventoryFilter::GetSingleton()->EquipFilter(a_actor, a_object)) {
                    LOG("EquipShoutHook restricted <{:08X}:{}>", a_object->GetFormID(), a_object->GetName())
                    return;
                }

                return func(a_manager, a_actor, a_object, a_slot);
            }

            static inline REL::Relocation<decltype(thunk)> func;

            static inline void Install() {
                std::array targets{std::make_pair(RELOCATION_ID(37941, 38897), REL::VariantOffset(0x21, 0x21, 0x21)),
                                   std::make_pair(RELOCATION_ID(37953, 38909), REL::VariantOffset(0x4B, 0x4B, 0x4B))};
                
                auto& trampoline = SKSE::GetTrampoline();

                for (const auto& [id, offset] : targets) {
                    REL::Relocation<std::uintptr_t> target{id, offset};
                    SKSE::AllocTrampoline(14);

                    func = trampoline.write_call<5>(target.address(), thunk);
                }
            }
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
            if (ConfigManager::GetSingleton()->GetVariable<bool>("Hooks.EquipSpell", true)) {
                EquipSpellHook::Install();
            }
            if (ConfigManager::GetSingleton()->GetVariable<bool>("Hooks.EquipShout", true)) {
                EquipShoutHook::Install();
            }

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