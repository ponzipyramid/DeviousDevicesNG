#include "InventoryFilter.h"
#include "Settings.h"
#include "UI.h"
#include "DeviceReader.h"

SINGLETONBODY(DeviousDevices::InventoryFilter)

namespace {
    int GetMaskForSlot(uint32_t slot) {
        if (slot < 29 || slot > 61) return 0;

        return (1 << (slot - 30));
    }
}

RE::TESObjectARMO* DeviousDevices::InventoryFilter::GetWornWithDeviousKeyword(RE::Actor* a_actor, RE::BGSKeyword* kwd) {

    std::unordered_map<RE::BGSKeyword*, RE::TESObjectARMO*> loc_itemMap;

    int slot = GetMaskForKeyword(a_actor, kwd);

    if (slot < 0) return nullptr;

    auto loc_armor = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(slot));

    if (loc_armor != nullptr && loc_armor->HasKeyword(kwd)) 
    {
        return loc_armor;
    }

    return nullptr;
}

bool DeviousDevices::InventoryFilter::TakeFilter(RE::Actor* a_actor, RE::TESBoundObject* obj) {
    if (!Settings::GetSingleton().GetSetting<bool>("mittensDropToggle") || obj == nullptr || !a_actor->IsPlayer() ||
        UI::GetMenu<RE::BarterMenu>().get())
        return false;

    if (!obj->Is(RE::FormType::Weapon) && !obj->Is(RE::FormType::KeyMaster) && (!obj->Is(RE::FormType::Armor) || IsDevious(obj)))
        return false;

    if (!GetWornWithDeviousKeyword(a_actor, _deviousBondageMittensKwd)) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0f, 100.0f);

    bool loc_rollFailure = distr(gen) < 80.0f;

    if (loc_rollFailure) {
        RE::DebugNotification("Locked in bondage mittens, you cannot pick up the item.");
    } else {
        RE::DebugNotification("Despite wearing bondage mittens, you manage to pick up the item.");
    }

    return loc_rollFailure;
}

bool DeviousDevices::InventoryFilter::ActorHasBlockingGag(RE::Actor* a_actor) {
    if (auto loc_armor = GetWornWithDeviousKeyword(a_actor, _deviousGagKwd)) {
        if (loc_armor->HasKeyword(_deviousGagKwd)) {
            if (loc_armor->HasKeyword(_deviousGagRingKwd))
                return false;  // is ring gag, do not remove food
            else if (loc_armor->HasKeyword(_deviousGagPanelKwd))  // is panel gag, additional check needed
            {
                return a_actor->GetFactionRank(_gagpanelfaction, true) == 1;
            }
            return true;
        }
    }
    return false;
}


bool DeviousDevices::InventoryFilter::EquipFilter(RE::Actor* a_actor, RE::TESBoundObject* a_item)
{
    if ((a_actor == nullptr) || (a_item == nullptr)) return true;
    
    auto loc_invMenu = UI::GetMenu<RE::InventoryMenu>();

    // == Gag check
    bool loc_needgagcheck = false;
    if (a_item->Is(RE::FormType::Ingredient)) //remove all ingredients
    {
        loc_needgagcheck = true;
    }
    else if (a_item->Is(RE::FormType::AlchemyItem)) //remove all food and potions (which are not poisons)
    {
        RE::AlchemyItem* loc_alchitem = a_item->As<RE::AlchemyItem>();
        if (!loc_alchitem->IsPoison()) loc_needgagcheck = true;
    }
    if (loc_needgagcheck && ActorHasBlockingGag(a_actor)) 
    {
        if (loc_invMenu.get()) {
            RE::DebugNotification("You can't eat or drink while wearing a gag.");
        }
        return true;
    }
    
    if ((a_item->Is(RE::FormType::Spell) || a_item->Is(RE::FormType::Weapon) || a_item->Is(RE::FormType::Light) ||
         (a_item->Is(RE::FormType::Armor) && !IsDevious(a_item) && !IsStrapon(a_item)))) {

        auto mittens = GetWornWithDeviousKeyword(a_actor, _deviousBondageMittensKwd);
        auto heavyBondage = GetWornWithDeviousKeyword(a_actor, _deviousHeavyBondageKwd);

        if (mittens || heavyBondage) {
            std::string msg = heavyBondage ? "You can't equip this with your hands tied!"
                                      : "You can't equip this while locked in bondage mittens!";

            if (loc_invMenu.get()) {
                RE::DebugNotification(msg.c_str());
            }

            return true;
        }
    }

    auto loc_dManager = DeviousDevices::DeviceReader::GetSingleton();

    if (loc_invMenu.get()) {
        if (auto loc_device = loc_dManager->GetDevice(a_item) ) {
            auto loc_invDevice = a_item->As<RE::TESObjectARMO>();
            auto loc_renDevice = loc_device->GetRenderedDevice();

            if (auto loc_wornArmor =
                    a_actor->GetWornArmor(loc_renDevice->GetArmorAddon(a_actor->GetRace())->GetSlotMask())) {
                if (loc_wornArmor->GetFormID() != loc_renDevice->GetFormID()) {
                    if (auto loc_otherInvDevice = loc_dManager->GetDeviceInventory(loc_wornArmor)) {
                        auto loc_otherDevice = loc_dManager->GetDevice(loc_otherInvDevice);
                    
                        std::string name = loc_otherDevice->deviceInventory->GetName();
                    
                        RE::DebugNotification(("You can't equip this due to " + name).c_str());

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool DeviousDevices::InventoryFilter::UnequipFilter(RE::Actor* a_actor, RE::TESBoundObject* a_item) {
    auto loc_dManager = DeviousDevices::DeviceReader::GetSingleton();
    
    if (a_actor->GetFormID() == 20) {
        LOG("Player Unequipping: {}", a_item->GetFormEditorID());
    }

    if (a_actor->GetFormID() == 20 && UI::GetMenu<RE::InventoryMenu>().get() && loc_dManager->GetDevice(a_item)) {
        LOG("Item Unequip Blocked: {}", a_item->GetFormEditorID());
        // invoke escape menu papyrus function or send event in some quest
        RE::DebugNotification("You can't unequip this device.");
        return true;
    }
    
    return false; 
}

bool DeviousDevices::InventoryFilter::IsDevious(RE::TESBoundObject* obj) {
    std::vector<RE::BGSKeyword*> loc_deviousKwds;
    loc_deviousKwds.push_back(_lockableKwd);
    loc_deviousKwds.push_back(_inventoryDeviceKwd);

    return obj->HasKeywordInArray(loc_deviousKwds, false) || obj->GetFormID() == _deviceHiderId;
}

bool DeviousDevices::InventoryFilter::IsStrapon(RE::TESBoundObject* obj) {
    std::vector<RE::BGSKeyword*> loc_straponKwds;
    loc_straponKwds.push_back(_sexlabNoStripKwd);
    loc_straponKwds.push_back(_jewelryKwd);

    return obj->HasKeywordInArray(loc_straponKwds, true);
}

int DeviousDevices::InventoryFilter::GetMaskForKeyword(RE::Actor* a_actor, RE::BGSKeyword* kwd) {
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
    else if (kwd == _deviousHeavyBondageKwd) {
        if (auto worn = a_actor->GetWornArmor(static_cast<RE::BIPED_MODEL::BipedObjectSlot>(32))) {
            if (worn->HasKeyword(_deviousStraitJacketKwd)) return GetMaskForSlot(32);
        }
        return GetMaskForSlot(46);
    } else if (kwd == _deviousPlugAnalKwd)
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

void DeviousDevices::InventoryFilter::Setup() {
    if (!_init) {
        _init = true;
        static RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();

        _sexlabNoStripKwd = loc_datahandler->LookupForm<RE::BGSKeyword>(0x02F16E, "Sexlab.esm");
        _jewelryKwd = loc_datahandler->LookupForm<RE::BGSKeyword>(0x02F16E, "Sexlab.esm");

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
    }
}