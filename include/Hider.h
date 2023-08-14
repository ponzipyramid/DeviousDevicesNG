#pragma once
#include <RE/Skyrim.h>

namespace DeviousDevices
{
    class DeviceHiderManager
    {
    SINGLETONHEADER(DeviceHiderManager)
    public:
        void Setup();
        std::vector<int> RebuildSlotMask(RE::Actor* a_actor, std::vector<int> a_slotfilter);
        int FilterMask(RE::Actor* a_actor, int a_slotmask);
        bool IsValidForHide(RE::TESObjectARMO* a_armor);
    protected:
        RE::BGSKeyword* _kwnohide = nullptr;
        RE::BGSKeyword* _kwlockable = nullptr;
        RE::BGSKeyword* _kwplug = nullptr;
        RE::BGSKeyword* _kwsos = nullptr;
        std::vector<RE::BGSKeyword*> _hidekeywords;
        std::vector<RE::BGSKeyword*> _nohidekeywords;
    };

    std::vector<int> RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotfilter);
    int FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask);
}