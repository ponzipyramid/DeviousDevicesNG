#pragma once
#include <RE/Skyrim.h>

namespace DeviousDevices
{
    class DeviceHiderManager
    {
<<<<<<< Updated upstream
    SINGLETONHEADER(DeviceHiderManager)
    public:
=======
    public:
        DeviceHiderManager(DeviceHiderManager &) = delete;
        void operator=(const DeviceHiderManager &) = delete;
        static DeviceHiderManager* GetSingleton();

>>>>>>> Stashed changes
        void Setup();
        std::vector<int> RebuildSlotMask(RE::Actor* a_actor, std::vector<int> a_slotfilter);
        int FilterMask(RE::Actor* a_actor, int a_slotmask);
        bool IsValidForHide(RE::TESObjectARMO* a_armor);
    protected:
<<<<<<< Updated upstream
        bool _setup                 = false;
        RE::BGSKeyword* _kwnohide   = nullptr;
        RE::BGSKeyword* _kwlockable = nullptr;
        RE::BGSKeyword* _kwplug     = nullptr;
        RE::BGSKeyword* _kwsos      = nullptr;
=======
        DeviceHiderManager(){}
        ~DeviceHiderManager(){}
        RE::BGSKeyword* _kwnohide = nullptr;
        RE::BGSKeyword* _kwlockable = nullptr;
        RE::BGSKeyword* _kwplug = nullptr;
        RE::BGSKeyword* _kwsos = nullptr;
>>>>>>> Stashed changes
        std::vector<RE::BGSKeyword*> _hidekeywords;
        std::vector<RE::BGSKeyword*> _nohidekeywords;
    };

    std::vector<int> RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotfilter);
    int FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask);
}