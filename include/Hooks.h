#pragma once

#include <detours/detours.h>

namespace DeviousDevices {
    typedef void(WINAPI* OriginalEquipObject)(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                              std::uint64_t a_extraData,
                                              std::uint32_t a_count, std::uint64_t a_slot, std::uint64_t a_queueEquip,
                                              std::uint64_t a_forceEquip, std::uint64_t a_playSounds,
                                              std::uint64_t a_applyNow);

    inline OriginalEquipObject _EquipObject;
    
    inline void EquipObject(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                            std::uint64_t a_extraData,
        std::uint32_t a_count, std::uint64_t a_slot, std::uint64_t a_queueEquip,
        std::uint64_t a_forceEquip, std::uint64_t a_playSounds, std::uint64_t a_applyNow) {

        SKSE::log::info("{} equipped {}", a_actor->GetFormID(), a_object->GetFormID());

        return _EquipObject(a_1, a_actor, a_object, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds, a_applyNow);

    }

    typedef void(WINAPI* OriginalUnequipObject)(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                                std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                                std::uint64_t a_queueEquip, std::uint64_t a_forceEquip,
                                                std::uint64_t a_playSounds, std::uint64_t a_applyNow,
                                                std::uint64_t a_slotToReplace);
    
    inline OriginalUnequipObject _UnequipObject;
    
    inline void UnequipObject(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                    std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                    std::uint64_t a_queueEquip, std::uint64_t a_forceEquip,
                                    std::uint64_t a_playSounds, std::uint64_t a_applyNow,
                                    std::uint64_t a_slotToReplace) {

        SKSE::log::info("{} unequipped {}", a_actor->GetFormID(), a_object->GetFormID());

        return _UnequipObject(a_1, a_actor, a_object, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip,
                              a_playSounds,
                         a_applyNow, a_slotToReplace);
    }

    inline void Install() {
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