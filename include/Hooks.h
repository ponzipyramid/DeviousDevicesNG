#pragma once

#include <detours/detours.h>

namespace DeviousDevices {
    typedef void(WINAPI* pFunc)(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                std::uint64_t a_queueEquip, std::uint64_t a_forceEquip, std::uint64_t a_playSounds,
                                std::uint64_t a_applyNow, std::uint64_t a_slotToReplace);
    inline pFunc originalFunction;
    
    inline void replacementFunction(std::uint64_t a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                    std::uint64_t a_extraData, std::uint64_t a_count, std::uint64_t a_slot,
                                    std::uint64_t a_queueEquip, std::uint64_t a_forceEquip,
                                    std::uint64_t a_playSounds, std::uint64_t a_applyNow,
                                    std::uint64_t a_slotToReplace) {

        SKSE::log::info("{} unequipped {}", a_actor->GetFormID(), a_object->GetFormID());

        return originalFunction(a_1, a_actor, a_object, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds,
                         a_applyNow, a_slotToReplace);
    }

    inline void Install() {
        const auto targetAddress = RE::Offset::ActorEquipManager::UnequipObject.address();
        const auto funcAddress = &replacementFunction;
        originalFunction = (pFunc)targetAddress;
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)originalFunction, (PBYTE)&replacementFunction);
        if (DetourTransactionCommit() == NO_ERROR)
            logger::info(
                "Installed papyrus hook on EquipItem at {0:x} with replacement from address {0:x}",
                targetAddress, (void*)funcAddress);
        else
            logger::warn("Failed to install papyrus hook on EquipItem");
    }
} 