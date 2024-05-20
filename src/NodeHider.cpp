#include "NodeHider.h"
#include "LibFunctions.h"
#include "Hider.h"
#include "Utils.h"

SINGLETONBODY(DeviousDevices::NodeHider)

void DeviousDevices::NodeHider::Setup()
{ 
    if (!_installed)
    {
        DEBUG("NodeHider::Setup() - called")
        _WeaponNodes = ConfigManager::GetSingleton()->GetArrayText("NodeHider.asWeaponNodes",false);
        _ArmNodes    = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asArmNodes");
        _straitjacket = RE::TESForm::LookupByEditorID<RE::BGSKeyword>("zad_DeviousStraitJacket");
        _installed = true;
        DEBUG("NodeHider::Setup() - complete")
    }
}

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

void DeviousDevices::NodeHider::UpdateWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    if (ShouldHideWeapons(a_actor)) HideWeapons(a_actor);
    else ShowWeapons(a_actor);
}

void DeviousDevices::NodeHider::UpdatePlayer(RE::Actor* a_actor)
{
    UniqueLock lock(SaveLock);

    if (a_actor == nullptr) return;

    UpdateArms(a_actor);
    UpdateWeapons(a_actor);
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


//void DeviousDevices::NodeHider::Update()
//{
//    //check ini if node hider should be used
//    if (!ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bEnabled",true)) return;
//
//    LOG("NodeHider::Update() - Updating...")
//
//    static RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton(); 
//
//    std::vector<RE::Actor*> loc_lastactors;
//    std::vector<RE::Actor*> loc_currentactors;
//
//    for (auto&& it : _lastupdatestack)
//    {
//        loc_lastactors.push_back(RE::Actor::LookupByHandle(it).get());
//    }
//
//    loc_currentactors.push_back(loc_player);
//
//    const int loc_distance = ConfigManager::GetSingleton()->GetVariable<int>("NodeHider.iNPCDistance",500);
//
//    Utils::ForEachActorInRange(loc_distance, [&](RE::Actor* a_actor) {
//        auto loc_refBase = a_actor->GetActorBase();
//        
//        if (a_actor && !a_actor->IsDisabled() && a_actor->Is3DLoaded() && !a_actor->IsPlayerRef() &&
//            (a_actor->Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)))) {
//            loc_currentactors.push_back(a_actor);
//        }
//    });
//
//    std::sort(loc_lastactors.begin(),loc_lastactors.end());
//    std::sort(loc_currentactors.begin(),loc_currentactors.end());
//
//    std::vector<RE::Actor*> loc_samectors(loc_lastactors.size() + loc_currentactors.size());
//    std::vector<RE::Actor*> loc_removedactors(loc_lastactors.size() + loc_currentactors.size());
//    std::vector<RE::Actor*> loc_addedactors(loc_lastactors.size() + loc_currentactors.size());
//
//    //get same actors -> should be already processed by node hider, so do nothing
//    auto loc_it1 = std::set_intersection(loc_lastactors.begin(), 
//                              loc_lastactors.end(), 
//                              loc_currentactors.begin(), 
//                              loc_currentactors.end(), 
//                              loc_samectors.begin());
//    loc_samectors.resize(loc_it1-loc_samectors.begin());
//
//    //get removed actors
//    auto loc_it2 = std::set_difference(loc_lastactors.begin(), 
//                              loc_lastactors.end(), 
//                              loc_samectors.begin(), 
//                              loc_samectors.end(), 
//                              loc_removedactors.begin());
//    loc_removedactors.resize(loc_it2-loc_removedactors.begin());
//
//    //get added actors
//    auto loc_it3 = std::set_difference(loc_currentactors.begin(), 
//                              loc_currentactors.end(), 
//                              loc_samectors.begin(), 
//                              loc_samectors.end(), 
//                              loc_addedactors.begin());
//    loc_addedactors.resize(loc_it3-loc_addedactors.begin());
//
//    const bool loc_hidearms = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArms",false);
//
//    //remove weapon node hider from removed actors
//    for (auto&& it : loc_removedactors)
//    {
//        //UpdateWapons(it);
//        if (loc_hidearms) UpdateArms(it);
//    }
//
//    //hide weapons for same actors, so it stay hidden
//    for (auto&& it : loc_samectors)
//    {
//        UpdateWapons(it);
//        if (loc_hidearms) UpdateArms(it);
//    }
//
//    //hide weapons for added actors
//    for (auto&& it : loc_addedactors)
//    {
//        UpdateWapons(it);
//        if (loc_hidearms) UpdateArms(it);
//    }
//
//    //update last actors
//    _lastupdatestack.clear();
//    for(auto&& it : loc_currentactors)
//    {
//        _lastupdatestack.push_back(it->GetHandle().native_handle());
//    }
//
//    LOG("NodeHider::Update() - Node hider updated")
//    LOG("NodeHider::Update() - Removed actors...")
//    for (auto&& it : loc_removedactors) LOG("\t{}",it ? it->GetName() : "NONE")
//    LOG("NodeHider::Update() - Same actors...")
//    for (auto&& it : loc_samectors) LOG("\t{}",it ? it->GetName() : "NONE")
//    LOG("NodeHider::Update() - Added actors...")
//    for (auto&& it : loc_addedactors) LOG("\t{}",it ? it->GetName() : "NONE")
//}

void DeviousDevices::NodeHider::UpdateTimed(RE::Actor* a_actor)
{
    UniqueLock lock(SaveLock);
    if (!a_actor) return;

    //LOG("NodeHider::UpdateTimed({}) called", a_actor ? a_actor->GetName() : "NONE")

    auto loc_refBase = a_actor->GetActorBase();
    if(a_actor->IsDisabled() || !a_actor->Is3DLoaded() || !(a_actor->Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC))))
    {
        LOG("NodeHider::UpdateTimed({}) - Actor is invalid",a_actor ? a_actor->GetName() : "NONE")
        return;
    }
    
    auto loc_id = _UpdatedActors.find(a_actor);

    if (loc_id == _UpdatedActors.end())
    {
        _UpdatedActors[a_actor] = {0,_UpdateCounter};
        LOG("NodeHider::UpdateTimed({}) - Actor registered",a_actor ? a_actor->GetName() : "NONE")
        return;
    }

    loc_id->second.elapsedFrames++;
    loc_id->second.lastUpdateFrame = _UpdateCounter;

    static bool loc_hidearms = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArms",false);

    static const int loc_updatetime = ConfigManager::GetSingleton()->GetVariable<int>("NodeHider.iNPCUpdateTime",60);

    if (loc_id->second.elapsedFrames >= loc_updatetime)
    {
        loc_id->second.elapsedFrames -= loc_updatetime;
        UpdateWeapons(a_actor);
        if (loc_hidearms) UpdateArms(a_actor);
    }
}

void DeviousDevices::NodeHider::Reload()
{
    UniqueLock lock(SaveLock);
    //UpdateWeapons(RE::PlayerCharacter::GetSingleton());
    //UpdateArms(RE::PlayerCharacter::GetSingleton());
    _UpdatedActors.clear();
    _lastupdatestack.clear();
    _armhiddenstates.clear();
    _weaponhiddenstates.clear();
}

void DeviousDevices::NodeHider::CleanUnusedActors()
{
    UniqueLock lock(SaveLock);
    for (auto&& [actor,updateHandle] : _UpdatedActors)
    {
        if ((updateHandle.lastUpdateFrame + 120) < _UpdateCounter)
        {
            _UpdatedActors.erase(actor);
        }
    }
}

void DeviousDevices::NodeHider::IncUpdateCounter()
{
    _UpdateCounter++;
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
    if (a_actor == nullptr || !a_actor->Is3DLoaded()) return false;

    auto loc_actor = a_actor->Get3D(false);
    if (loc_actor == nullptr) return false;
    
    RE::NiNode* loc_thirdpersonNode = loc_actor->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;
    
    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    
    if (loc_node != nullptr && loc_node->AsNode()->local.scale >= 0.5f)
    {
        loc_node->AsNode()->local.scale = 0.002f;
        _weaponnodestates[a_actor->GetHandle().native_handle()][a_nodename] = HidderState::sHidden;
        return true;
    }
    return false;
}

bool DeviousDevices::NodeHider::RemoveHideNode(RE::Actor* a_actor, std::string a_nodename)
{
    if (a_actor == nullptr || !a_actor->Is3DLoaded()) return false;

    auto loc_actor = a_actor->Get3D(false);
    if (loc_actor == nullptr) return false;
        
    RE::NiNode* loc_thirdpersonNode = loc_actor->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;
    
    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    if (loc_node != nullptr && _weaponnodestates[a_actor->GetHandle().native_handle()][a_nodename] == HidderState::sHidden)
    {
        loc_node->AsNode()->local.scale = 1.00f;
        _weaponnodestates[a_actor->GetHandle().native_handle()][a_nodename] = HidderState::sShown;
        return true;
    }
    return false;
}