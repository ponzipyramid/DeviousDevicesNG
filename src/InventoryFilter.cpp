#include "InventoryFilter.h"

DeviousDevices::InventoryFilter* DeviousDevices::InventoryFilter::_this = new DeviousDevices::InventoryFilter;

DeviousDevices::InventoryFilter* DeviousDevices::InventoryFilter::GetSingleton()
{
    return _this;
}

void DeviousDevices::InventoryFilter::Setup()
{
    if (!_init)
    {
        _init = true;
        auto* eventSink = MenuEvent::GetSingleton();
        RE::UI::GetSingleton()->AddEventSink<RE::MenuOpenCloseEvent>(eventSink);

        static RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        _gagkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x007EB8,"Devious Devices - Assets.esm")));              //default gag keyword
        _gagringkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x08C854,"Devious Devices - Integration.esm")));     //ring gag keyword
        _gagpanelkeyword.push_back(static_cast<RE::BGSKeyword*>(loc_datahandler->LookupForm(0x01F306,"Devious Devices - Assets.esm")));         //panel gag keyword
        _gagpanelfaction = static_cast<RE::TESFaction*>(loc_datahandler->LookupForm(0x030C3C,"Devious Devices - Integration.esm"));             //panel gag faction
    }
}

void DeviousDevices::InventoryFilter::HookMethodsIM()
{
    if (!_hookedIM)
    {
        _hookedIM = true;
        RE::UI* loc_ui = RE::UI::GetSingleton();
        if (loc_ui == nullptr) return;
        RE::GPtr<RE::InventoryMenu> loc_imenu = loc_ui->GetMenu<RE::InventoryMenu>(RE::InventoryMenu::MENU_NAME);
        if (loc_imenu == nullptr) return;
        HookVirtualMethod<RE::InventoryMenu,decltype(PostDisplayIM)>(loc_imenu.get(),0x06,0x06,reinterpret_cast<uintptr_t>(PostDisplayIM),PostDisplayIM_old);
    }
}

void DeviousDevices::InventoryFilter::HookMethodsFM()
{
    if (!_hookedFM)
    {
        _hookedFM = true;
        RE::UI* loc_ui = RE::UI::GetSingleton();
        if (loc_ui == nullptr) return;
        RE::GPtr<RE::FavoritesMenu> loc_favmenu = loc_ui->GetMenu<RE::FavoritesMenu>(RE::FavoritesMenu::MENU_NAME);
        if (loc_favmenu == nullptr) return;
        HookVirtualMethod<RE::FavoritesMenu,decltype(PostDisplayFM)>(loc_favmenu.get(),0x06,0x06,reinterpret_cast<uintptr_t>(PostDisplayFM),PostDisplayFM_old);
    }
}

bool DeviousDevices::InventoryFilter::PlayerHaveGag()
{
    //check that player have gag
    static RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton();
    for(int i = 0x00000001; i != 0x40000000; i <<= 1)
    {
        //get armor from slot
        RE::TESObjectARMO* loc_armor = loc_player->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(i));
        if (loc_armor != nullptr)
        {
            if (loc_armor->HasKeywordInArray(_gagkeyword,false)) 
            {
                if (loc_armor->HasKeywordInArray(_gagringkeyword,false)) return false;  //is ring gag, do not remove food
                else if (loc_armor->HasKeywordInArray(_gagpanelkeyword,false))          //is panel gag, additional check needed
                {
                    //check if panel gag is plugged
                    if (loc_player->GetFactionRank(_gagpanelfaction,true) == 1) return true;
                    else return false;
                }
                return true;
            }
        }
    }
    return false;
}

void DeviousDevices::InventoryFilter::PostDisplayIM(RE::InventoryMenu* a_this)
{
    static InventoryFilter* loc_filter = InventoryFilter::GetSingleton();

    //only remove consumable items if player is gagged
    if (loc_filter->PlayerHaveGag())
    {
        bool loc_removed = false;
        for(int i = 0; i < a_this->GetRuntimeData().itemList->items.size();i++)
        {
            RE::InventoryEntryData* loc_item = a_this->GetRuntimeData().itemList->items[i]->data.objDesc;
            if (loc_item != nullptr)
            {
                bool loc_valide = false;

                if (loc_item->object->Is(RE::FormType::Ingredient)) //remove all ingredients
                {
                    loc_valide = true;
                }
                else if (loc_item->object->Is(RE::FormType::AlchemyItem)) //remove all food and potions (which are not poisons)
                {
                   RE::AlchemyItem* loc_alchitem = reinterpret_cast<RE::AlchemyItem*>(loc_item->object);
                   if (!loc_alchitem->IsPoison()) loc_valide = true;
                }

                if (loc_valide)
                {
                    a_this->GetRuntimeData().itemList->entryList.RemoveElement(i);
                    a_this->GetRuntimeData().itemList->items.erase(a_this->GetRuntimeData().itemList->items.begin() + i);
                    loc_removed = true;
                }
            }
        }

        if (loc_removed)
        {
            //update item list, so the item tabs can be updated (grayed out)
            static std::string  loc_path = ("_level0.Menu_mc.inventoryLists.InvalidateListData");
            a_this->uiMovie->InvokeNoReturn(loc_path.c_str(),NULL,0);
            a_this->uiMovie->Advance(0.0f);
        }
    }
    PostDisplayIM_old(a_this);
}


// Currently doesn't work as intended. Removing items work, but UI doesn't get updated, so clicking on buttons will result in different items being activated
// Will have to contact someone who knows more about AS and SkyUi for help
void DeviousDevices::InventoryFilter::PostDisplayFM(RE::FavoritesMenu* a_this)
{
    static InventoryFilter* loc_filter = InventoryFilter::GetSingleton();

    //only remove consumable items if player is gagged
    if (loc_filter->PlayerHaveGag())
    {
        bool loc_removed = false;
        for(int i = 0; i < a_this->GetRuntimeData().favorites.size();i++)
        {
            RE::InventoryEntryData* loc_item = a_this->GetRuntimeData().favorites[i].entryData;
            if (loc_item != nullptr)
            {
                bool loc_valide = false;

                if (loc_item->object->Is(RE::FormType::Ingredient)) //remove all ingredients
                {
                    loc_valide = true;
                }
                else if (loc_item->object->Is(RE::FormType::AlchemyItem)) //remove all food and potions (which are not poisons)
                {
                   RE::AlchemyItem* loc_alchitem = reinterpret_cast<RE::AlchemyItem*>(loc_item->object);
                   if (!loc_alchitem->IsPoison()) loc_valide = true;
                }

                if (loc_valide)
                {
                    RE::InventoryChanges* loc_invchang = RE::PlayerCharacter::GetSingleton()->GetInventoryChanges();
                    RE::ExtraDataList* loc_xdata = nullptr;
                    if (loc_item->extraLists) {
                        for (const auto& xList : *loc_item->extraLists) {
                            if (const auto hotkey = xList->HasType<RE::ExtraHotkey>()) {
                                loc_xdata = xList;
                            }
                        }
                    }
                    
                    loc_invchang->RemoveFavorite(loc_item,loc_xdata);
                    loc_removed = true;
                }
            }
        }

        if (loc_removed)
        {
            //does nothing :)
            static std::string  loc_path = ("Menu_mc.FavoritesMenu.itemList.UpdateList");
            a_this->uiMovie->InvokeNoReturn(loc_path.c_str(),NULL,0);
            a_this->uiMovie->Advance(0.0f);
        }
    }
    PostDisplayFM_old(a_this);
}

RE::BSEventNotifyControl DeviousDevices::MenuEvent::ProcessEvent(const RE::MenuOpenCloseEvent* event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
{
    if (event->opening)
    {
        if ((event->menuName == RE::InventoryMenu::MENU_NAME)) InventoryFilter::GetSingleton()->HookMethodsIM();
        else if ((event->menuName == RE::FavoritesMenu::MENU_NAME)) InventoryFilter::GetSingleton()->HookMethodsFM();
    }
    return RE::BSEventNotifyControl::kContinue;
}
