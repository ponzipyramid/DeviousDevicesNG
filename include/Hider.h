#pragma once
#include <RE/Skyrim.h>

namespace DeviousDevices
{
    std::vector<int> RebuildSlotMask(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<int> a_slotusage, std::vector<int> a_slotfilter);
    int FilterMask(PAPYRUSFUNCHANDLE,RE::Actor* a_actor, int a_slotmask);

    bool _IsValidForHide(RE::TESObjectARMO* a_armor);

}