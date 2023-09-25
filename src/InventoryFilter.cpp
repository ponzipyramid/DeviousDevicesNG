#include "InventoryFilter.h"

SINGLETONBODY(DeviousDevices::InventoryFilter)

void DeviousDevices::InventoryFilter::Setup()
{
    if (!_init)
    {
        _init = true;

        static RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        _gagkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x007EB8,"Devious Devices - Assets.esm")));              //default gag keyword
        _gagringkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x08C854,"Devious Devices - Integration.esm")));     //ring gag keyword
        _gagpanelkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x01F306,"Devious Devices - Assets.esm")));         //panel gag keyword
        _gagpanelfaction = static_cast<RE::TESFaction*>(loc_datahandler->LookupForm(0x030C3C,"Devious Devices - Integration.esm"));             //panel gag faction
    }
}

bool DeviousDevices::InventoryFilter::ActorHaveGag(RE::Actor* a_actor)
{
    //check that actor have gag
    for(int i = 0x00000001; i != 0x40000000; i <<= 1)
    {
        //get armor from slot
        RE::TESObjectARMO* loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i));
        if (loc_armor != nullptr)
        {
            if (loc_armor->HasKeywordInArray(_gagkeyword,false)) 
            {
                if (loc_armor->HasKeywordInArray(_gagringkeyword,false)) return false;  //is ring gag, do not remove food
                else if (loc_armor->HasKeywordInArray(_gagpanelkeyword,false))          //is panel gag, additional check needed
                {
                    //check if panel gag is plugged
                    if (a_actor->GetFactionRank(_gagpanelfaction,true) == 1) return true;
                    else return false;
                }
                return true;
            }
        }
    }
    return false;
}

bool DeviousDevices::InventoryFilter::Filter(RE::Actor* a_actor, RE::TESBoundObject* a_item)
{
    if ((a_actor == nullptr) || (a_item == nullptr)) return true;

    // == Gag check
    bool loc_needgagcheck = false;
    if (a_item->Is(RE::FormType::Ingredient)) //remove all ingredients
    {
        loc_needgagcheck = true;
    }
    else if (a_item->Is(RE::FormType::AlchemyItem)) //remove all food and potions (which are not poisons)
    {
        RE::AlchemyItem* loc_alchitem = reinterpret_cast<RE::AlchemyItem*>(a_item);
        if (!loc_alchitem->IsPoison()) loc_needgagcheck = true;
    }
    if (loc_needgagcheck && ActorHaveGag(a_actor)) 
    {
        // item is food, and actor have gag -> prevent item from being consumed
        return true;
    }

    return false;
}
