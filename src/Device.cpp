#include "Device.h"
#include "Script.hpp"
#include "RE/A/AttachedScript.h"

using namespace DeviousDevices;

void Device::Init(RE::TESDataHandler* handler) {
    inventory = GetForm<RE::TESObjectARMO>(handler);
    rendered = renderedInfo.GetForm<RE::TESObjectARMO>(handler);

    if (!inventory)
        SKSE::log::info("{} inventory device not found", editorId);
    else
        formId = inventory->GetFormID();
    if (!rendered) SKSE::log::info("{} rendered device not found", editorId);

    
    equipConflictingDeviceKwds.Init(handler);
    requiredDeviceKwds.Init(handler);
    unequipConflictingDeviceKwds.Init(handler);

    kwd = kwdInfo.GetForm<RE::BGSKeyword>(handler);

    equipMenu = equipMenuInfo.GetForm<RE::BGSMessage>(handler);
}

bool Device::CanEquip(RE::Actor* actor) {
    std::vector<RE::BGSKeyword*> conflictKwds = equipConflictingDeviceKwds.GetKwds();

    conflictKwds.push_back(kwd);

    std::vector<RE::BGSKeyword*> requiredKwds = requiredDeviceKwds.GetKwds();
    std::unordered_set<RE::BGSKeyword*> seen;

    RE::TESObjectREFR::InventoryItemMap itemMap = actor->GetInventory();
    
    // add generic script name checks


    for (auto& [item, value] : itemMap) {
        RE::TESObjectREFR* refr = item->As<RE::TESObjectREFR>();

        if (!refr) continue;

        if (refr->HasKeywordInArray(conflictKwds, false)) return false;
        
        for (auto kwd : requiredKwds)
            if (refr->HasKeyword(kwd)) seen.insert(kwd);
    }

    return seen.size() == requiredKwds.size();
}