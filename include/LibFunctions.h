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
        RE::BGSListForm* _busyFactionsListForm; // TODO: FLM/KID events for `SKSE::GetModCallbackEventSource()->AddEventSink`,
                                                // and preload Faction forms in Setup and merge to `_busyFactions` (compatibility with FLM)
        std::vector<RE::TESFaction*> _busyFactions;
    };

    std::vector<RE::TESObjectARMO*> GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn);
    RE::TESObjectARMO* GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy);
    bool zad_isActorBusy(PAPYRUSFUNCHANDLE, RE::Actor* a_actor);
}