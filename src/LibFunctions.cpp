#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::LibFunctions)

void DeviousDevices::LibFunctions::Setup()
{
    RE::TESDataHandler* handler = RE::TESDataHandler::GetSingleton();

    // TODO: FLM/KID events, and preload Faction forms in Setup and merge with _zadAnimatingFaction, _sexlabAnimatingFaction
    _busyFactionsListForm = handler->LookupForm<RE::BGSListForm>(0x08CE36, "Devious Devices - Integration.esm"); // new empty zad_BusyFactions Form List

    auto zadAnimatingFaction = handler->LookupForm<RE::TESFaction>(0x029567, "Devious Devices - Integration.esm"); // zadAnimatingFaction
    if (zadAnimatingFaction) {
        _busyFactions.push_back(zadAnimatingFaction);
    }

    auto sexLabAnimatingFaction = handler->LookupForm<RE::TESFaction>(0x00E50F, "SexLab.esm");  // SexLabAnimatingFaction
    if (sexLabAnimatingFaction) {
        _busyFactions.push_back(sexLabAnimatingFaction);
    }
}

std::vector<RE::TESObjectARMO*> DeviousDevices::LibFunctions::GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn)
{
    std::vector<RE::TESObjectARMO*> loc_res;
    if (a_actor == nullptr) return loc_res;

    if (a_worn)
    {
        for (uint32_t loc_mask = 0x00000001U; loc_mask != 0x80000000U ;loc_mask <<= 1U)
        {
            RE::TESObjectARMO* loc_deviceRD = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(loc_mask));
            if (loc_deviceRD != nullptr)
            {
                
                if (auto loc_device = DeviceReader::GetSingleton()->LookupDeviceByRendered(loc_deviceRD))
                {
                    if (a_mode == 0) loc_res.push_back(loc_device->deviceInventory);
                    else loc_res.push_back(loc_device->deviceRendered);
                }
            }
        }
    }
    else
    {
        RE::Actor::InventoryItemMap loc_inv = a_actor->GetInventory();
        for (auto&& it : loc_inv)
        {
            RE::TESBoundObject* loc_obj = it.first;
            if ((loc_obj != nullptr) && loc_obj->IsArmor())
            {
                RE::TESObjectARMO* loc_deviceID = loc_obj->As<RE::TESObjectARMO>();
                RE::TESObjectARMO* loc_deviceRD = DeviceReader::GetSingleton()->GetDeviceRender(loc_deviceID);
                if ((loc_deviceID != nullptr) && (loc_deviceRD != nullptr))
                {
                    if (a_mode == 0) loc_res.push_back(loc_deviceID);
                    else loc_res.push_back(loc_deviceRD);
                }
            }
        }
    }
    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy) {
    if ((a_actor == nullptr) || (a_kw == nullptr)) return nullptr;
    for (uint32_t loc_mask = 0x00000001U; loc_mask != 0x80000000U ;loc_mask <<= 1U)
    {
        RE::TESObjectARMO* loc_deviceRD = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(loc_mask));
        if (loc_deviceRD != nullptr)
        {
            auto loc_device = DeviceReader::GetSingleton()->LookupDeviceByRendered(loc_deviceRD);
            LOG("GetWornDevice: before")
            if (loc_device != nullptr && ((!a_fuzzy && loc_device->kwd == a_kw) || (a_fuzzy && loc_deviceRD->HasKeyword(a_kw))))
            {
                LOG("GetWornDevice: inside")
                return loc_device->deviceInventory;
            }
        }
    }
    return nullptr;
}

bool DeviousDevices::LibFunctions::isActorBusy(RE::Actor* a_actor) {
    // 1. Sit/Mount; TODO: sitstate?
    if (a_actor->IsOnMount()) {
        LOG("isActorBusy: Actor {} on Mount or sit", a_actor->GetName())
        return true;
    }

    // 2. Check _busyFactions
    for (const RE::TESFaction* faction : _busyFactions) {
        if (a_actor->IsInFaction(faction)) {
            LOG("isActorBusy: Actor {} in Animation Faction {}", a_actor->GetName(), faction->GetName())
            return true;
        }
    }

    // TODO: FLM/KID events, and preload Faction forms in Setup
    // 3. Check _busyFactionsListForm
    if (_busyFactionsListForm) {
        for (auto&& faction : _busyFactionsListForm->forms) {
            if (faction->Is(RE::FormType::Faction) &&
                a_actor->IsInFaction(static_cast<RE::TESFaction*>(faction))) {
                LOG("isActorBusy: Actor {} in {} Factions", a_actor->GetName(), faction->GetName())
                return true;
            }
        }
    }

    // 4. Check Keywords ?

    // 5. Check Quests/Scenes ?

    return false;
}

std::vector<RE::TESObjectARMO*> DeviousDevices::GetDevices(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_mode, bool a_worn)
{
    LOG("GetDevices called")
    return LibFunctions::GetSingleton()->GetDevices(a_actor,a_mode,a_worn);
}

RE::TESObjectARMO* DeviousDevices::GetWornDevice(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, RE::BGSKeyword* a_kw,
                                                 bool a_fuzzy) {
    LOG("GetWornDevice called")
    return LibFunctions::GetSingleton()->GetWornDevice(a_actor, a_kw, a_fuzzy);
}

bool DeviousDevices::zad_isActorBusy(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
{
    LOG("zad_isActorBusy called")
    return LibFunctions::GetSingleton()->isActorBusy(a_actor);
}