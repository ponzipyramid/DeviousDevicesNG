#pragma once

#include <RE/Skyrim.h>
#include <REL/Relocation.h>

namespace DeviousDevices
{
    class InventoryFilter
    {
    SINGLETONHEADER(InventoryFilter)
    public:
        void Setup();
        bool ActorHaveGag(RE::Actor* a_actor);

        //return true if equip operation should be filter out (no item state will be changed)
        bool Filter(RE::Actor* a_actor, RE::TESBoundObject* a_item);

    private:
        bool _init = false;
        std::vector<RE::BGSKeyword*>    _gagkeyword;
        std::vector<RE::BGSKeyword*>    _gagringkeyword;
        std::vector<RE::BGSKeyword*>    _gagpanelkeyword;
        RE::TESFaction*                 _gagpanelfaction;
    };
}