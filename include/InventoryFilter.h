#pragma once

#include <RE/Skyrim.h>
#include <REL/Relocation.h>

namespace DeviousDevices {
    class InventoryFilter {
        SINGLETONHEADER(InventoryFilter)
    public:
        void Setup();

        bool TakeFilter(RE::Actor* a_actor, RE::TESBoundObject* obj);
        bool EquipFilter(RE::Actor* a_actor, RE::TESBoundObject* a_item);
        bool UnequipFilter(RE::Actor* a_actor, RE::TESBoundObject* a_item);

        RE::TESObjectARMO* GetWornWithDeviousKeyword(RE::Actor* actor, RE::BGSKeyword* kwd);

    private:
        bool IsDevious(RE::TESBoundObject* obj);
        bool IsStrapon(RE::TESBoundObject* obj);
        bool ActorHasBlockingGag(RE::Actor* a_actor);
        int GetMaskForKeyword(RE::Actor* a_actor, RE::BGSKeyword* kwd);

        bool _init = false;

        // misc
        RE::FormID _deviceHiderId;

        // factions
        RE::TESFaction* _gagpanelfaction;

        // keywords
        RE::BGSKeyword* _sexlabNoStripKwd;
        RE::BGSKeyword* _jewelryKwd;

        RE::BGSKeyword* _deviousPlugKwd;
        RE::BGSKeyword* _deviousBeltKwd;
        RE::BGSKeyword* _deviousBraKwd;
        RE::BGSKeyword* _deviousCollarKwd;
        RE::BGSKeyword* _deviousArmCuffsKwd;
        RE::BGSKeyword* _deviousLegCuffsKwd;
        RE::BGSKeyword* _deviousArmbinderKwd;
        RE::BGSKeyword* _deviousArmbinderElbowKwd;
        RE::BGSKeyword* _deviousHeavyBondageKwd;
        RE::BGSKeyword* _deviousHobbleSkirtKwd;
        RE::BGSKeyword* _deviousHobbleSkirtRelaxedKwd;
        RE::BGSKeyword* _deviousAnkleShacklesKwd;
        RE::BGSKeyword* _deviousStraitJacketKwd;
        RE::BGSKeyword* _deviousCuffsFrontKwd;
        RE::BGSKeyword* _deviousPetSuitKwd;
        RE::BGSKeyword* _deviousYokeKwd;
        RE::BGSKeyword* _deviousYokeBBKwd;
        RE::BGSKeyword* _deviousCorsetKwd;
        RE::BGSKeyword* _deviousClampsKwd;
        RE::BGSKeyword* _deviousGlovesKwd;
        RE::BGSKeyword* _deviousHoodKwd;
        RE::BGSKeyword* _deviousSuitKwd;
        RE::BGSKeyword* _deviousElbowTieKwd;
        RE::BGSKeyword* _deviousGagKwd;
        RE::BGSKeyword* _deviousGagRingKwd;
        RE::BGSKeyword* _deviousGagLargeKwd;
        RE::BGSKeyword* _deviousGagPanelKwd;
        RE::BGSKeyword* _deviousPlugVaginalKwd;
        RE::BGSKeyword* _deviousPlugAnalKwd;
        RE::BGSKeyword* _deviousHarnessKwd;
        RE::BGSKeyword* _deviousBlindfoldKwd;
        RE::BGSKeyword* _deviousBootsKwd;
        RE::BGSKeyword* _deviousPiercingsNippleKwd;
        RE::BGSKeyword* _deviousPiercingsVaginalKwd;
        RE::BGSKeyword* _deviousBondageMittensKwd;
        RE::BGSKeyword* _deviousPonyGearKwd;

        RE::BGSKeyword* _permitOralKwd;
        RE::BGSKeyword* _permitAnalKwd;
        RE::BGSKeyword* _permitVaginalKwd;

        RE::BGSKeyword* _lockableKwd;
        RE::BGSKeyword* _inventoryDeviceKwd;
    };
}  // namespace DeviousDevices