#pragma once
#include <RE/Skyrim.h>
#include <detours/detours.h>

namespace DeviousDevices
{

    typedef std::uint32_t(WINAPI* OriginalGetWornMask)(RE::InventoryChanges*);

    class DeviceHiderManager
    {
    SINGLETONHEADER(DeviceHiderManager)
    public:
        void Setup();
        std::vector<int> RebuildSlotMask(RE::Actor* a_actor, std::vector<int> a_slotfilter);
        int FilterMask(RE::Actor* a_actor, int a_slotmask);
        bool IsValidForHide(RE::TESObjectARMO* a_armor);
    protected:
        bool _setup                 = false;
        RE::BGSKeyword* _kwnohide   = nullptr;
        RE::BGSKeyword* _kwlockable = nullptr;
        RE::BGSKeyword* _kwplug     = nullptr;
        RE::BGSKeyword* _kwsos      = nullptr;
        std::vector<RE::BGSKeyword*> _hidekeywords;
        std::vector<RE::BGSKeyword*> _nohidekeywords;
        static inline OriginalGetWornMask  _GetWornMask;
        static std::uint32_t GetWornMask(RE::InventoryChanges* a_this);

        static RE::BSContainer::ForEachResult GetWornMask_Visit(void* a_this, RE::InventoryEntryData* a_entryData);
        inline static REL::Relocation<decltype(GetWornMask_Visit)> GetWornMask_Visit_old;
    };



    std::vector<int> RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotfilter);
    int FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask);
}