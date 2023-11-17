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

    //LOG("LibFunctions::GetWornDevice({},{},{}) called",a_actor->GetName(),a_kw->GetFormEditorID(),a_fuzzy)

    RE::TESObjectARMO* loc_res = nullptr;
    auto loc_visitor = WornVisitor([this,&loc_res,a_kw,a_fuzzy](RE::InventoryEntryData* a_entry)
    {
        #undef GetObject
        //LOG("LibFunctions::GetWornDevice() - Visited = {} {:08X}",a_entry->GetDisplayName(),a_entry->GetObject()->GetFormID())

        auto loc_object = a_entry->GetObject();
        RE::TESObjectARMO* loc_armor = nullptr;
        if (loc_object != nullptr && loc_object->IsArmor())
        {
            loc_armor = static_cast<RE::TESObjectARMO*>(loc_object);
        }

        if (loc_armor != nullptr && loc_armor->HasKeywordInArray(_rdkw,false))
        {
            auto loc_device = DeviceReader::GetSingleton()->LookupDeviceByRendered(loc_armor);
            if (loc_device && ((!a_fuzzy && loc_device->kwd == a_kw) || (a_fuzzy && loc_armor->HasKeyword(a_kw))))
            {
                loc_res = loc_device->deviceInventory;
                //LOG("LibFunctions::GetWornDevice - Worn device found, res = {} {:08X}",loc_device->GetName(),loc_device->GetFormID())
                return RE::BSContainer::ForEachResult::kStop;
            }
            else if (loc_device == nullptr)
            {
                WARN("Could not find device unit for device {:08X} because of db error, or because device is of legacy type",loc_armor->GetFormID())
                return RE::BSContainer::ForEachResult::kStop;
            }
            else
            {
                return RE::BSContainer::ForEachResult::kContinue;
            }
        }
        else
        {
            return RE::BSContainer::ForEachResult::kContinue;
        }
    });

    a_actor->GetInventoryChanges()->VisitWornItems(loc_visitor.AsNativeVisitor());

    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetHandRestrain(RE::Actor* a_actor)
{
    return GetWornDevice(a_actor,_hbkw,true);
}

bool DeviousDevices::LibFunctions::IsBound(RE::Actor* a_actor) const
{
    return WornHasKeyword(a_actor,_hbkw);
}

bool DeviousDevices::LibFunctions::WornHasKeyword(RE::Actor* a_actor, RE::BGSKeyword* a_kw) const
{
    if ((a_actor == nullptr) || (a_kw == nullptr)) return false;

    //LOG("LibFunctions::WornHasKeyword({},{}) called",a_actor->GetName(),a_kw->GetFormEditorID())

    bool loc_res = false;
    auto loc_visitor = WornVisitor([this,&loc_res,a_kw](RE::InventoryEntryData* a_entry)
    {
        #undef GetObject
        auto loc_object = a_entry->GetObject();
        RE::TESObjectARMO* loc_armor = nullptr;
        if (loc_object != nullptr && loc_object->IsArmor()) loc_armor = static_cast<RE::TESObjectARMO*>(loc_object);

        if (loc_armor != nullptr && loc_armor->HasKeyword(a_kw))
        {
            loc_res = true;
            return RE::BSContainer::ForEachResult::kStop;
        }
        else return RE::BSContainer::ForEachResult::kContinue;
    });
    a_actor->GetInventoryChanges()->VisitWornItems(loc_visitor.AsNativeVisitor());
    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::LibFunctions::GetWornArmor(RE::Actor* a_actor, int a_mask) const
{
    if (a_actor == nullptr) return nullptr;

    //LOG("LibFunctions::GetWornArmor({},{:08X}) called",a_actor->GetName(),a_mask)

    RE::TESObjectARMO* loc_res = nullptr;
    auto loc_visitor = WornVisitor([this,&loc_res,a_mask](RE::InventoryEntryData* a_entry)
    {
        #undef GetObject
        auto loc_object = a_entry->GetObject();
        RE::TESObjectARMO* loc_armor = nullptr;
        if (loc_object != nullptr && loc_object->IsArmor()) loc_armor = static_cast<RE::TESObjectARMO*>(loc_object);

        if (loc_armor != nullptr && ((int)loc_armor->GetSlotMask() & a_mask))
        {
            loc_res = loc_armor;
            return RE::BSContainer::ForEachResult::kStop;
        }
        else return RE::BSContainer::ForEachResult::kContinue;
    });
    a_actor->GetInventoryChanges()->VisitWornItems(loc_visitor.AsNativeVisitor());
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
