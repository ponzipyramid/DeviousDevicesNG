#include "NodeHider.h"
#include "LibFunctions.h"
#include "Hider.h"

SINGLETONBODY(DeviousDevices::NodeHider)


void DeviousDevices::NodeHider::HideArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = _armhiddenstates[a_actor->GetHandle().native_handle()];
    if (loc_state == HidderState::sHidden) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0)->AsNode();
    if (thirdpersonNode == nullptr) return;

    for (auto&& it : _ArmNodes)
    {
        RE::NiNode* loc_node = thirdpersonNode->GetObjectByName(it)->AsNode();
        if (loc_node != nullptr) loc_node->local.scale = 0.002f;
        else ERROR("NodeHider::HideArms - Cant find node {}",it)
    }

    _armhiddenstates[a_actor->GetHandle().native_handle()] = HidderState::sHidden;

    LOG("NodeHider::HideArms({}) - Arm nodes hidden",a_actor->GetName())
}

void DeviousDevices::NodeHider::ShowArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = _armhiddenstates[a_actor->GetHandle().native_handle()];
    if (loc_state == HidderState::sShown) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0)->AsNode();
    if (thirdpersonNode == nullptr) return;

    for (auto&& it : _ArmNodes)
    {
        RE::NiNode* loc_node = thirdpersonNode->GetObjectByName(it)->AsNode();
        if (loc_node != nullptr) loc_node->local.scale = 1.000f;
        else ERROR("NodeHider::ShowArms - Cant find node {}",it)
    }

    _armhiddenstates[a_actor->GetHandle().native_handle()] = HidderState::sShown;

    LOG("NodeHider::ShowArms({}) - Arm nodes shown",a_actor->GetName())
}

void DeviousDevices::NodeHider::UpdateArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    if (LibFunctions::GetSingleton()->WornHasKeyword(a_actor,_straitjacket)) HideArms(a_actor);
    else ShowArms(a_actor);
}

void DeviousDevices::NodeHider::UpdateWapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    if (ShouldHideWeapons(a_actor)) HideWeapons(a_actor);
    else ShowWeapons(a_actor);
}

void DeviousDevices::NodeHider::HideWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = _weaponhiddenstates[a_actor->GetHandle().native_handle()];
    //if (loc_state == HidderState::sHidden) return;

    for (auto&& it : _WeaponNodes)
    {
        AddHideNode(a_actor,it);
    }

    _weaponhiddenstates[a_actor->GetHandle().native_handle()] = HidderState::sHidden;

    LOG("NodeHider::HideWeapons({}) - Weapon nodes hidden",a_actor->GetName())
}

void DeviousDevices::NodeHider::ShowWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = _weaponhiddenstates[a_actor->GetHandle().native_handle()];
    if (loc_state == HidderState::sShown) return;

    for (auto&& it : _WeaponNodes)
    {
        RemoveHideNode(a_actor,it);
    }

    _weaponhiddenstates[a_actor->GetHandle().native_handle()] = HidderState::sShown;

    LOG("NodeHider::ShowWeapons({}) - Weapon nodes shown",a_actor->GetName())
}

void DeviousDevices::NodeHider::Setup()
{ 
    if (!_installed)
    {
        DEBUG("NodeHider::Setup() - Installed")
        _WeaponNodes = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asWeaponNodes");
        _ArmNodes    = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asArmNodes");
        _straitjacket = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousStraitJacket");
        _installed = true;
    }
}

void DeviousDevices::NodeHider::Update()
{
    //check ini if node hider should be used
    if (!ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bEnabled",true)) return;

    LOG("NodeHider::Update() - Updating...")

    static RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton(); 

    std::vector<RE::Actor*> loc_lastactors;
    std::vector<RE::Actor*> loc_currentactors;

    for (auto&& it : _lastupdatestack)
    {
        loc_lastactors.push_back(RE::Actor::LookupByHandle(it).get());
    }

    const int loc_distance = ConfigManager::GetSingleton()->GetVariable<int>("NodeHider.iNPCDistance",2000);

    RE::TES::GetSingleton()->ForEachReferenceInRange(loc_player, loc_distance, [&](RE::TESObjectREFR& a_ref) {
        auto loc_refBase    = a_ref.GetBaseObject();
        auto loc_actor      = a_ref.As<RE::Actor>();
        if (loc_actor && (loc_actor == loc_player) || (a_ref.Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)))) 
        {
            loc_currentactors.push_back(loc_actor);
        }
        return RE::BSContainer::ForEachResult::kContinue;
    });

    std::sort(loc_lastactors.begin(),loc_lastactors.end());
    std::sort(loc_currentactors.begin(),loc_currentactors.end());

    std::vector<RE::Actor*> loc_samectors(loc_lastactors.size() + loc_currentactors.size());
    std::vector<RE::Actor*> loc_removedactors(loc_lastactors.size() + loc_currentactors.size());
    std::vector<RE::Actor*> loc_addedactors(loc_lastactors.size() + loc_currentactors.size());

    //get same actors -> should be already processed by node hider, so do nothing
    auto loc_it1 = std::set_intersection(loc_lastactors.begin(), 
                              loc_lastactors.end(), 
                              loc_currentactors.begin(), 
                              loc_currentactors.end(), 
                              loc_samectors.begin());
    loc_samectors.resize(loc_it1-loc_samectors.begin());

    //get removed actors
    auto loc_it2 = std::set_difference(loc_lastactors.begin(), 
                              loc_lastactors.end(), 
                              loc_samectors.begin(), 
                              loc_samectors.end(), 
                              loc_removedactors.begin());
    loc_removedactors.resize(loc_it2-loc_removedactors.begin());

    //get added actors
    auto loc_it3 = std::set_difference(loc_currentactors.begin(), 
                              loc_currentactors.end(), 
                              loc_samectors.begin(), 
                              loc_samectors.end(), 
                              loc_addedactors.begin());
    loc_addedactors.resize(loc_it3-loc_addedactors.begin());

    const bool loc_hidearms = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArms",false);

    //remove weapon node hider from removed actors
    for (auto&& it : loc_removedactors)
    {
        //UpdateWapons(it);
        if (loc_hidearms) UpdateArms(it);
    }

    //hide weapons for same actors, so it stay hidden
    for (auto&& it : loc_samectors)
    {
        UpdateWapons(it);
        if (loc_hidearms) UpdateArms(it);
    }

    //hide weapons for added actors
    for (auto&& it : loc_addedactors)
    {
        UpdateWapons(it);
        if (loc_hidearms) UpdateArms(it);
    }

    //update last actors
    _lastupdatestack.clear();
    for(auto&& it : loc_currentactors)
    {
        _lastupdatestack.push_back(it->GetHandle().native_handle());
    }

    LOG("NodeHider::Update() - Node hider updated")
    LOG("NodeHider::Update() - Removed actors...")
    for (auto&& it : loc_removedactors) LOG("\t{}",it ? it->GetName() : "NONE")
    LOG("NodeHider::Update() - Same actors...")
    for (auto&& it : loc_samectors) LOG("\t{}",it ? it->GetName() : "NONE")
    LOG("NodeHider::Update() - Added actors...")
    for (auto&& it : loc_addedactors) LOG("\t{}",it ? it->GetName() : "NONE")
}

void DeviousDevices::NodeHider::Reload()
{
    _lastupdatestack.clear();
    _armhiddenstates.clear();
    _weaponhiddenstates.clear();
}

bool DeviousDevices::NodeHider::ActorIsValid(RE::Actor* a_actor) const
{
    if (a_actor == nullptr) return false;
    
    if (a_actor->IsDead() || !a_actor->Is3DLoaded() || a_actor->IsDisabled())
    {
        return false;
    }
    return true;
}

bool DeviousDevices::NodeHider::ShouldHideWeapons(RE::Actor* a_actor) const
{
    if (!ActorIsValid(a_actor)) return false;
    return LibFunctions::GetSingleton()->IsAnimating(a_actor) || (LibFunctions::GetSingleton()->IsBound(a_actor));
}

bool DeviousDevices::NodeHider::AddHideNode(RE::Actor* a_actor, std::string a_nodename)
{
    if (a_actor == nullptr) return false;
    
    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(false)->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;
    
    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    if (loc_node != nullptr)
    {
        loc_node->AsNode()->local.scale = 0.00f;
        return true;
    }
    return false;
}

bool DeviousDevices::NodeHider::RemoveHideNode(RE::Actor* a_actor, std::string a_nodename)
{
    if (a_actor == nullptr) return false;
        
    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(false)->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;
    
    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    if (loc_node != nullptr)
    {
            loc_node->AsNode()->local.scale = 1.00f;
            return true;
    }
    return false;
}