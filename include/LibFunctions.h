#pragma once
#include <RE/Skyrim.h>
#include <DeviceReader.h>

namespace DeviousDevices
{
    class LibFunctions
    {
    SINGLETONHEADER(LibFunctions)
    public:
        std::vector<RE::TESObjectARMO*> GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn);
        RE::TESObjectARMO*              GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw);
    };

    std::vector<RE::TESObjectARMO*> GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn);
    RE::TESObjectARMO*              GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw);
}