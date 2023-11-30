#pragma once
#include <RE/Skyrim.h>
#include <DeviceReader.h>

namespace DeviousDevices
{
    class LibFunctions
    {
    SINGLETONHEADER(LibFunctions)
    public:
        void Setup();
        std::vector<RE::TESObjectARMO*> GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn);
        RE::TESObjectARMO* GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy);
        bool isActorBusy(RE::Actor* a_actor);

    private:
        RE::BGSListForm* _busyFactionsListForm;
        RE::TESFaction* _zadAnimatingFaction;
        RE::TESFaction* _sexlabAnimatingFaction;
    };

    std::vector<RE::TESObjectARMO*> GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn);
    RE::TESObjectARMO* GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy);
    bool zad_isActorBusy(PAPYRUSFUNCHANDLE, RE::Actor* a_actor);
}