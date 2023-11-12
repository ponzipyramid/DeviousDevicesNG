#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::LibFunctions)

void DeviousDevices::LibFunctions::Setup()
{
    if (!_installed)
    {
        RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        if (loc_datahandler == nullptr) 
        {
            LOG("LibFunctions::Setup() - loc_datahandler = NULL -> cant setup!")
            return;
        }

        auto loc_kwid = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x02B5F0,"Devious Devices - Integration.esm"));
        if (loc_kwid != nullptr) _idkw.push_back(loc_kwid);


        auto loc_kwlockable = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x003894,"Devious Devices - Assets.esm"));
        auto loc_kwplug     = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x003331,"Devious Devices - Assets.esm"));

        if (loc_kwlockable  != nullptr) _rdkw.push_back(loc_kwlockable);
        if (loc_kwplug      != nullptr) _rdkw.push_back(loc_kwplug);

        _hbkw = static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x05226C,"Devious Devices - Integration.esm"));  //zad_DeviousHeavyBondage

        auto loc_ddanimationfaction = static_cast<RE::TESFaction*>(loc_datahandler->LookupForm(0x029567,"Devious Devices - Integration.esm"));  //dd animation faction
        auto loc_slanimationfaction = static_cast<RE::TESFaction*>(loc_datahandler->LookupForm(0x00E50F,"SexLab.esm"));  //sexlab animation faction

        if (loc_ddanimationfaction != nullptr) _animationfactions.push_back(loc_ddanimationfaction);
        if (loc_slanimationfaction != nullptr) _animationfactions.push_back(loc_slanimationfaction);

        LOG("LibFunctions::Setup() - Installed")
        _installed = true;
    }

}

std::vector<RE::TESObjectARMO*> DeviousDevices::LibFunctions::GetDevices(RE::Actor* a_actor, int a_mode, bool a_worn)
{
    std::vector<RE::TESObjectARMO*> loc_res;
    if (a_actor == nullptr) return loc_res;

    RE::Actor::InventoryItemMap loc_inv = a_actor->GetInventory([this,a_mode](RE::TESBoundObject& a_obj)
    {
        switch (a_mode)
        {
        case 0: //inventory devices
            return a_obj.IsArmor() && a_obj.HasKeywordInArray(_idkw,false); 
        case 1: //render devices
            return a_obj.IsArmor() && a_obj.HasKeywordInArray(_rdkw,false);
        default:  //error mode
            return false;
        }
    });

    for (auto&& [i_obj, i_item] : loc_inv)
    {
        if (i_obj != nullptr && ((!a_worn) || ((i_item.second != nullptr) && (i_item.second->IsWorn()))))
        {
            if ((i_obj->As<RE::TESObjectARMO>() != nullptr))
            {
                if (a_mode == 0) loc_res.push_back(i_obj->As<RE::TESObjectARMO>());
                else loc_res.push_back(i_obj->As<RE::TESObjectARMO>());
            }
        }
    }

    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetWornDevice(RE::Actor* a_actor, RE::BGSKeyword* a_kw, bool a_fuzzy) {
    if ((a_actor == nullptr) || (a_kw == nullptr)) return nullptr;

    RE::Actor::InventoryItemMap loc_inv = a_actor->GetInventory([this](RE::TESBoundObject& a_obj)
    {
        return a_obj.IsArmor() && a_obj.HasKeywordInArray(_rdkw,false);
    });

    for (auto&& [i_obj, i_item] : loc_inv)
    {
        if (i_obj != nullptr && (i_item.second != nullptr) && (i_item.second->IsWorn()))
        {
            RE::TESObjectARMO* loc_deviceRD = i_obj->As<RE::TESObjectARMO>();
            if (loc_deviceRD != nullptr)
            {
                auto loc_device = DeviceReader::GetSingleton()->LookupDeviceByRendered(loc_deviceRD);
                if (loc_device && ((!a_fuzzy && loc_device->kwd == a_kw) || (a_fuzzy && loc_deviceRD->HasKeyword(a_kw))))
                {
                    return loc_device->deviceInventory;
                }
                else if (loc_device == nullptr)
                {
                    WARN("Could not find device unit for device {:08X} because of db error, or because device is of legacy type",loc_deviceRD->GetFormID())
                }
            }
        }
    }
    return nullptr;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetHandRestrain(RE::Actor* a_actor)
{
    RE::TESObjectARMO* loc_res = GetWornDevice(a_actor,_hbkw,true);
    if (a_actor != nullptr)
    {
        LOG("GetHandRestrain({}) - res = {}",a_actor->GetName(),loc_res ? loc_res->GetName() : "NONE")
    }
    return loc_res;
}

bool DeviousDevices::LibFunctions::IsAnimating(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return false;
    for (auto&& it : _animationfactions)
    {
        if ((it != nullptr) && a_actor->IsInFaction(it)) return true;
    }
    return false;
}
