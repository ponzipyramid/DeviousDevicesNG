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

    private:
        bool _installed = false;
        std::vector<RE::BGSKeyword*> _idkw;
        std::vector<RE::BGSKeyword*> _rdkw;
    };

    inline std::vector<RE::TESObjectARMO*> GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn)
    {
        LOG("GetDevices called")
        return LibFunctions::GetSingleton()->GetDevices(a_actor,a_mode,a_worn);
    }
    inline RE::TESObjectARMO* GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy) 
    {
        LOG("GetWornDevice called")
        return LibFunctions::GetSingleton()->GetWornDevice(a_actor, a_kw, a_fuzzy);
    }
}