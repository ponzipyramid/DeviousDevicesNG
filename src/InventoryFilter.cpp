#include "InventoryFilter.h"
#include "Settings.h"
#include "UI.h"
#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::InventoryFilter)

namespace 
{
    constexpr int GetMaskForSlot(uint32_t slot) 
    {
        if (slot < 29 || slot > 61) return 0;

        return (1 << (slot - 30));
    }
}

RE::TESObjectARMO* DeviousDevices::InventoryFilter::GetWornWithDeviousKeyword(RE::Actor* a_actor, RE::BGSKeyword* kwd) 
{
    const int loc_slot = GetMaskForKeyword(a_actor, kwd);

    if (loc_slot < 0) return nullptr;

    const auto loc_armor = LibFunctions::GetSingleton()->GetWornArmor(a_actor,loc_slot);
    //const auto loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(loc_slot));

    if (loc_armor != nullptr && loc_armor->HasKeyword(kwd)) 
    {
        return loc_armor;
    }

    return nullptr;
}

bool DeviousDevices::InventoryFilter::TakeFilter(RE::Actor* a_actor, RE::TESBoundObject* obj)
{
    if (!Settings::GetSingleton().GetSetting<bool>("mittensDropToggle") || obj == nullptr || obj->GetName() == "" ||
        a_actor->GetFormID() != 20 || UI::GetMenu<RE::BarterMenu>().get())
        return false;

    if (!obj->Is(RE::FormType::Weapon) && !obj->Is(RE::FormType::KeyMaster) && (!obj->Is(RE::FormType::Armor) || IsDevious(obj)))
        return false;

    if (!GetWornWithDeviousKeyword(a_actor, _deviousBondageMittensKwd)) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0f, 100.0f);

    bool loc_rollFailure = distr(gen) < 80.0f;

    if (loc_rollFailure) 
    {
        RE::DebugNotification("Locked in bondage mittens, you cannot pick up the item.");
    }
    else
    {
        RE::DebugNotification("Despite wearing bondage mittens, you manage to pick up the item.");
    }

    return loc_rollFailure;
}

bool DeviousDevices::InventoryFilter::ActorHasBlockingGag(RE::Actor* a_actor, RE::TESObjectARMO* a_gag) 
{
    RE::TESObjectARMO* loc_armor = nullptr;
    if (a_gag) loc_armor = a_gag;
    else loc_armor = LibFunctions::GetSingleton()->GetWornArmor(a_actor,GetMaskForSlot(44));
    
    if (loc_armor != nullptr)
    {
        if (loc_armor->HasKeyword(_deviousGagKwd))
        {
            if (loc_armor->HasKeyword(_deviousGagRingKwd) || loc_armor->HasKeyword(_PermitOralKwd))
            {
                return false;  // is ring gag, do not remove food
            }
            else if (loc_armor->HasKeyword(_deviousGagPanelKwd))  // is panel gag, additional check needed
            {
                return a_actor->GetFactionRank(_gagpanelfaction, a_actor->IsPlayer()) == 1;
            }
            return true;
        }
    }
    return false;
}

bool DeviousDevices::InventoryFilter::EquipFilter(RE::Actor* a_actor, RE::TESBoundObject* a_item)
{
    if ((a_actor == nullptr) || (a_item == nullptr)) return true;

    // item have no name -> most likely used internaly by other mod, and not equipped by player -> never filter it out
    // or is SMP object used by 3BA
    if (!CheckWhitelist(a_item)) return false;

    // == Gag check
    bool loc_needgagcheck = false;

    if (a_item->Is(RE::FormType::Ingredient)) //filter all ingredients
    {
        loc_needgagcheck = true;
    }
    else if (a_item->Is(RE::FormType::AlchemyItem)) //filter all food and potions (which are not poisons)
    {
        RE::AlchemyItem* loc_alchitem = a_item->As<RE::AlchemyItem>();
        if (!loc_alchitem->IsPoison()) loc_needgagcheck = true;
    }

    bool loc_checkinventory = false;
    if (loc_needgagcheck)
    {
        if (!CheckWhitelistFood(a_item)) return false; //check food filter
        if (ConfigManager::GetSingleton()->GetVariable<bool>("InventoryFilter.bGagFilterModeMenu",false) == 1) loc_checkinventory = true;

        // UI can be still not loaded even after save is loaded. 
        // Because of that it is important to always check that UI singleton is initiated
        RE::GPtr<RE::InventoryMenu> loc_invMenu = nullptr;
        if (RE::UI::GetSingleton() != nullptr)
        {
            loc_invMenu = UI::GetMenu<RE::InventoryMenu>();
        }
        else ERROR("Cant check if inventory menu is open because UI singleton is not initiated")

        if ((!loc_checkinventory || loc_invMenu.get()) && ActorHasBlockingGag(a_actor)) 
        {
            RE::DebugNotification("You can't eat or drink while wearing this gag.");
            return true;
        }
    }

    if (a_item->Is(RE::FormType::Shout) && ActorHasBlockingGag(a_actor))  // filter all Shouts
    {
        RE::GPtr<RE::MagicMenu> loc_magMenu = nullptr;
        if (RE::UI::GetSingleton() != nullptr) {
            loc_magMenu = UI::GetMenu<RE::MagicMenu>();
        } else
            ERROR("Cant check if inventory menu is open because UI singleton is not initiated")

        if (loc_magMenu.get()) {
            RE::DebugNotification("You can't equip this while wearing this gag!");
        }
        return true;
    }

    // == Equip check
    if ((a_item->Is(RE::FormType::Spell) || a_item->Is(RE::FormType::Weapon) || a_item->Is(RE::FormType::Light) ||
         (a_item->Is(RE::FormType::Armor) && !IsDevious(a_item) && !IsStrapon(a_item)))) 
    {
        const bool loc_heavyBondage   = GetWornWithDeviousKeyword(a_actor, _deviousHeavyBondageKwd);
        const bool loc_mittens        = !loc_heavyBondage && GetWornWithDeviousKeyword(a_actor, _deviousBondageMittensKwd);
        
        if (loc_heavyBondage || loc_mittens) 
        {
            const std::string loc_msg = loc_heavyBondage ? "You can't equip this with your hands tied!"
                                      : "You can't equip this while locked in bondage mittens!";

            // UI can be still not loaded even after save is loaded. 
            // Because of that it is important to always check that UI singleton is initiated
            RE::GPtr<RE::InventoryMenu> loc_invMenu = nullptr;
            RE::GPtr<RE::MagicMenu> loc_magMenu = nullptr;
            if (RE::UI::GetSingleton() != nullptr)
            {
                loc_invMenu = UI::GetMenu<RE::InventoryMenu>();
                loc_magMenu = UI::GetMenu<RE::MagicMenu>();
            }
            else ERROR("Cant check if inventory menu is open because UI singleton is not initiated")

            if (loc_invMenu.get() || loc_magMenu.get()) 
            {
                RE::DebugNotification(loc_msg.c_str());
            }

            return true;
        }
    }

    return false;
}

bool DeviousDevices::InventoryFilter::IsDevious(RE::TESBoundObject* obj)
{
    static std::vector<RE::BGSKeyword*> loc_deviousKwds = {_lockableKwd,_inventoryDeviceKwd};
    return obj->HasKeywordInArray(loc_deviousKwds, false);
}

bool DeviousDevices::InventoryFilter::IsStrapon(RE::TESBoundObject* obj)
{
    static std::vector<RE::BGSKeyword*> loc_straponKwds = {_sexlabNoStripKwd,_jewelryKwd};
    return obj->HasKeywordInArray(loc_straponKwds, true);
}

int DeviousDevices::InventoryFilter::GetMaskForKeyword(RE::Actor* a_actor, RE::BGSKeyword* kwd)
{
    if (kwd == _deviousArmCuffsKwd)
        return GetMaskForSlot(59);
    else if (kwd == _deviousGagKwd)
        return GetMaskForSlot(44);
    else if (kwd == _deviousHarnessKwd)
        return GetMaskForSlot(58);
    else if (kwd == _deviousCorsetKwd)
        return GetMaskForSlot(58);
    else if (kwd == _deviousCollarKwd)
        return GetMaskForSlot(45);
    else if (kwd == _deviousHeavyBondageKwd) 
    {
        if (auto worn = a_actor->GetWornArmor(RE::BIPED_MODEL::BipedObjectSlot::kBody)) 
        {
            if (worn->HasKeyword(_deviousStraitJacketKwd)) return GetMaskForSlot(32);
        }
        return GetMaskForSlot(46);
    } 
    else if (kwd == _deviousPlugAnalKwd)
        return GetMaskForSlot(48);
    else if (kwd == _deviousBeltKwd)
        return GetMaskForSlot(49);
    else if (kwd == _deviousPiercingsVaginalKwd)
        return GetMaskForSlot(50);
    else if (kwd == _deviousPiercingsNippleKwd)
        return GetMaskForSlot(51);
    else if (kwd == _deviousLegCuffsKwd)
        return GetMaskForSlot(53);
    else if (kwd == _deviousBlindfoldKwd)
        return GetMaskForSlot(55);
    else if (kwd == _deviousBraKwd)
        return GetMaskForSlot(56);
    else if (kwd == _deviousPlugVaginalKwd)
        return GetMaskForSlot(57);
    else if (kwd == _deviousSuitKwd)
        return GetMaskForSlot(32);
    else if (kwd == _deviousGlovesKwd)
        return GetMaskForSlot(33);
    else if (kwd == _deviousHoodKwd)
        return GetMaskForSlot(30);
    else if (kwd == _deviousBootsKwd)
        return GetMaskForSlot(37);
    else if (kwd == _deviousBondageMittensKwd)
        return GetMaskForSlot(33);
    else
        return -1;
}

bool DeviousDevices::InventoryFilter::CheckWhitelist(const RE::TESBoundObject* a_item) const
{
    if (a_item == nullptr) return false;
    auto loc_whitelist = ConfigManager::GetSingleton()->GetArray<std::string>("InventoryFilter.asWhitelist");

    std::string loc_name = a_item->GetName();
    std::transform(loc_name.begin(), loc_name.end(), loc_name.begin(), ::tolower); //to lower case

    if (loc_name == "") return false;

    //check whitelist
    for (auto&& it : loc_whitelist)
    {
        if ((it != "") && (it != " ") && (loc_name.find(it) != std::string::npos)) return false;
    }

    return true;
}

bool DeviousDevices::InventoryFilter::CheckWhitelistFood(const RE::TESBoundObject* a_item) const
{
    if (a_item == nullptr) return false;
    auto loc_whitelist = ConfigManager::GetSingleton()->GetArray<std::string>("InventoryFilter.asWhitelistFood");

    std::string loc_name = a_item->GetName();
    std::transform(loc_name.begin(), loc_name.end(), loc_name.begin(), ::tolower); //to lower case

    if (loc_name == "") return false;

    //check whitelist
    for (auto&& it : loc_whitelist)
    {
        if ((it != "") && (it != " ") && (loc_name.find(it) != std::string::npos)) return false;
    }

    return true;
}

void DeviousDevices::InventoryFilter::Setup() 
{
    if (!_init)
    {
        _init = true;
        static RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        _sexlabNoStripKwd = loc_datahandler->LookupForm<RE::BGSKeyword>(0x02F16E, "Sexlab.esm");
        _jewelryKwd = loc_datahandler->LookupForm<RE::BGSKeyword>(0x02F16E, "Sexlab.esm");
        
        _gagpanelfaction = RE::TESForm::LookupByEditorID<RE::TESFaction>("zadGagPanelFaction");

        _deviousPlugKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPlug");
        _deviousBeltKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousBelt");
        _deviousBraKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousBra");
        _deviousCollarKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousCollar");
        _deviousArmCuffsKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousArmCuffs");
        _deviousLegCuffsKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousLegCuffs");
        _deviousArmbinderKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousArmbinder");
        _deviousArmbinderElbowKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousArmbinderElbow");
        _deviousHeavyBondageKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousHeavyBondage");
        _deviousHobbleSkirtKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousHobbleSkirt");
        _deviousHobbleSkirtRelaxedKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousHobbleSkirtRelaxed");
        _deviousAnkleShacklesKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousAnkleShackles");
        _deviousStraitJacketKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousStraitJacket");
        _deviousCuffsFrontKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousCuffsFront");
        _deviousPetSuitKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPetSuit");
        _deviousYokeKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousYoke");
        _deviousYokeBBKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousYokeBB");
        _deviousCorsetKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousCorset");
        _deviousClampsKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousClamps");
        _deviousGlovesKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousGloves");
        _deviousHoodKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousHood");
        _deviousSuitKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousSuit");
        _deviousElbowTieKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousElbowTie");
        _deviousGagKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousGag");
        _deviousGagRingKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousGagRing");
        _deviousGagLargeKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousGagLarge");
        _deviousGagPanelKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousGagPanel");
        _deviousPlugVaginalKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPlugVaginal");
        _deviousPlugAnalKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPlugAnal");
        _deviousHarnessKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousHarness");
        _deviousBlindfoldKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousBlindfold");
        _deviousBootsKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousBoots");
        _deviousPiercingsNippleKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPiercingsNipple");
        _deviousPiercingsVaginalKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPiercingsVaginal");
        _deviousBondageMittensKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousBondageMittens");
        _deviousPonyGearKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousPonyGear");

        _permitOralKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_PermitOral");
        _permitAnalKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_PermitAnal");
        _permitVaginalKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_PermitVaginal");


        _lockableKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_Lockable");
        _inventoryDeviceKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_InventoryDevice");

        _PermitOralKwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_PermitOral");
    }
}