#pragma once
#include <RE/Skyrim.h>
#include <detours/detours.h>
#include "DeviceReader.h"

namespace DeviousDevices
{
    class DeviceHiderManager
    {
    SINGLETONHEADER(DeviceHiderManager)
    public:
        void                    Setup();
        std::vector<int>        RebuildSlotMask(RE::Actor* a_actor, std::vector<int> a_slotfilter);
        int                     FilterMask(RE::Actor* a_actor, int a_slotmask);
        bool                    IsValidForHide(RE::TESObjectARMO* a_armor) const;
        void                    SyncSetting(std::vector<int> a_masks);
        const std::vector<int>& GetSetting() const;
        inline bool             ProcessHider(RE::TESObjectARMO* a_armor, RE::Actor* a_actor);
    protected:
        bool _setup                 = false;
        RE::BGSKeyword* _kwnohide   = nullptr;
        RE::BGSKeyword* _kwlockable = nullptr;
        RE::BGSKeyword* _kwplug     = nullptr;
        RE::BGSKeyword* _kwsos      = nullptr;
        std::vector<RE::BGSKeyword*> _hidekeywords;
        std::vector<RE::BGSKeyword*> _nohidekeywords;


        std::atomic_bool _CheckResult = false;

        void CheckHiderSlots(RE::TESObjectARMO* a_armor, RE::Actor* a_actor, uint32_t a_min, uint32_t a_max);

        std::vector<int> _setting;

        //=== copied from Dynamic Armor Variables ===
        //returns true if addon have passed race
        static bool HasRace(RE::TESObjectARMA* a_armorAddon, RE::TESRace* a_race);

        //render armor addon on actor (?)
        static void InitWornArmorAddon(RE::TESObjectARMA* a_armorAddon,RE::TESObjectARMO* a_armor,RE::BSTSmartPointer<RE::BipedAnim>* a_biped,RE::SEX a_sex);

        //called every once in the while by game to update 3d models on actor
        static void InitWornArmor(RE::TESObjectARMO* a_armor,RE::Actor* a_actor,RE::BSTSmartPointer<RE::BipedAnim>* a_biped);

    };

    inline void SyncSetting(PAPYRUSFUNCHANDLE,std::vector<int> a_slotfilter)
    {
        LOG("SyncSetting called")
        DeviceHiderManager::GetSingleton()->SyncSetting(a_slotfilter);
    }
}