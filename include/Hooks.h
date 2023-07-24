#pragma once

#include <detours/detours.h>

namespace DeviousDevices {
    typedef void(WINAPI* pFunc)(RE::ActorEquipManager a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object, RE::ExtraDataList* a_extraData,
                                std::uint32_t a_count, const RE::BGSEquipSlot* a_slot, bool a_queueEquip,
                                bool a_forceEquip, bool a_playSounds, bool a_applyNow,
                                const RE::BGSEquipSlot* a_slotToReplace);
    inline pFunc originalFunction;
    
    inline void replacementFunction(RE::ActorEquipManager a_1, RE::Actor* a_actor, RE::TESBoundObject* a_object,
                                    RE::ExtraDataList* a_extraData,
                                    std::uint32_t a_count, const RE::BGSEquipSlot* a_slot, bool a_queueEquip,
                                    bool a_forceEquip, bool a_playSounds, bool a_applyNow,
                                    const RE::BGSEquipSlot* a_slotToReplace) {
        SKSE::log::info("Test");

        return originalFunction(a_1, a_actor, a_object, a_extraData, a_count, a_slot, a_queueEquip, a_forceEquip, a_playSounds,
                         a_applyNow, a_slotToReplace);
    }

    void Install() {
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