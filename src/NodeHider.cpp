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

        _ArmNodes       = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asArmNodes");
        _HandNodes      = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asHandNodes");
        _FingerNodes    = ConfigManager::GetSingleton()->GetArray<std::string>("NodeHider.asFingerNodes");

        _ArmHiddingKeywords     = ConfigManager::GetSingleton()->GetArrayText("NodeHider.asArmHiddingKeywords",false);
        _HandHiddingKeywords    = ConfigManager::GetSingleton()->GetArrayText("NodeHider.asHandHiddingKeywords",false);
        _FingerHiddingKeywords  = ConfigManager::GetSingleton()->GetArrayText("NodeHider.asFingerHiddingKeywords",false);

        DEBUG("NodeHider::Setup() - Hidding nodes")
        for (auto&& it : _ArmNodes) DEBUG("Arm node: {}",it)
        for (auto&& it : _HandNodes) DEBUG("Hand node: {}",it)
        for (auto&& it : _FingerNodes) DEBUG("Finger node: {}",it)
        DEBUG("NodeHider::Setup() - Hidding keywords")
        for (auto&& it : _ArmHiddingKeywords) DEBUG("Arm kw: {}",it)
        for (auto&& it : _HandHiddingKeywords) DEBUG("Hand kw: {}",it)
        for (auto&& it : _FingerHiddingKeywords) DEBUG("Finger kw: {}",it)

        _installed = true;
        DEBUG("NodeHider::Setup() - complete")
    }
}

void DeviousDevices::NodeHider::HideArmNodes(RE::Actor* a_actor, std::unordered_map<uint32_t, HidderState>& a_states, std::vector<std::string> a_nodes)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = a_states[a_actor->GetHandle().native_handle()];
    if (loc_state == HidderState::sHidden) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0)->AsNode();
    if (thirdpersonNode == nullptr) return;

    static bool loc_hidefirstperson = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArmsFirstPerson",true);

    RE::NiNode* firstpersonnode = loc_hidefirstperson ? a_actor->Get3D(1)->AsNode() : nullptr;
    if (loc_hidefirstperson && firstpersonnode == nullptr) return;

    LOG("NodeHider::HideArmNodes({}) called",a_actor->GetName())

    for (auto&& it : a_nodes)
    {
        RE::NiNode* loc_node = thirdpersonNode->GetObjectByName(it)->AsNode();
        if (loc_node != nullptr) 
        {
            loc_node->local.scale = 0.002f;
            LOG("NodeHider::ShowArmNode - Third person node {} hidden",it)
        }
        else ERROR("NodeHider::HideArmNodes - Cant find third person node {}",it)

        if (loc_hidefirstperson)
        {
            RE::NiNode* loc_nodefp = firstpersonnode->GetObjectByName(it)->AsNode();
            if (loc_nodefp != nullptr) 
            {
                loc_nodefp->local.scale = 0.002f;
                LOG("NodeHider::ShowArmNode - First person node {} hidden",it)
            }
            else ERROR("NodeHider::HideArmNodes - Cant find first person node {}",it)
        }
    }

    a_states[a_actor->GetHandle().native_handle()] = HidderState::sHidden;
}

void DeviousDevices::NodeHider::ShowArmNodes(RE::Actor* a_actor, std::unordered_map<uint32_t, HidderState>& a_states, std::vector<std::string> a_nodes)
{
    if (a_actor == nullptr) return;

    HidderState loc_state = a_states[a_actor->GetHandle().native_handle()];
    if (loc_state == HidderState::sShown) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0) ? a_actor->Get3D(0)->AsNode() : nullptr;
    if (thirdpersonNode == nullptr) return;

    static bool loc_hidefirstperson = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArmsFirstPerson",true);

    RE::NiNode* firstpersonnode = loc_hidefirstperson ? (a_actor->Get3D(1) ? a_actor->Get3D(1)->AsNode() : nullptr) : nullptr;
    if (loc_hidefirstperson && firstpersonnode == nullptr) return;

    LOG("NodeHider::ShowArmNodes({}) called",a_actor->GetName())

    for (auto&& it : a_nodes)
    {
        RE::NiNode* loc_node    = thirdpersonNode->GetObjectByName(it)->AsNode();
        
        if (loc_node != nullptr) 
        {
            loc_node->local.scale = 1.000f;
            LOG("NodeHider::ShowArmNode - Third person node {} shown",it)
        }
        else ERROR("NodeHider::ShowArmNodes - Cant find third person node {}",it)

        if (loc_hidefirstperson)
        {
            RE::NiNode* loc_nodefp  = firstpersonnode->GetObjectByName(it)->AsNode();
            if (loc_nodefp != nullptr) 
            {
                loc_nodefp->local.scale = 1.000f;
                LOG("NodeHider::ShowArmNode - First person node {} shown",it)
            }
            else ERROR("NodeHider::ShowArmNodes - Cant find first person node {}",it)
        }
    }

    a_states[a_actor->GetHandle().native_handle()] = HidderState::sShown;
}

void DeviousDevices::NodeHider::UpdateArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr)
    {
        ERROR("NodeHider::UpdateArms() - Actor is none")
        return;
    }

    //LOG("NodeHider::UpdateArms({}) called",a_actor->GetName())

    // Arms
    {
        const auto loc_hidearms = std::find_if(_ArmHiddingKeywords.begin(),_ArmHiddingKeywords.end(),[a_actor](const std::string& a_kw)
        {
            return LibFunctions::GetSingleton()->WornHasKeyword(a_actor,a_kw);
        });
        if (loc_hidearms != _ArmHiddingKeywords.end()) HideArmNodes(a_actor,_armhiddenstates,_ArmNodes);
        else ShowArmNodes(a_actor,_armhiddenstates,_ArmNodes);
    }

    // Hands
    {
        const auto loc_hidehands = std::find_if(_HandHiddingKeywords.begin(),_HandHiddingKeywords.end(),[a_actor](const std::string& a_kw)
        {
            return LibFunctions::GetSingleton()->WornHasKeyword(a_actor,a_kw);
        });
        if (loc_hidehands != _HandHiddingKeywords.end()) HideArmNodes(a_actor,_handhiddenstates,_HandNodes);
        else ShowArmNodes(a_actor,_handhiddenstates,_HandNodes);
    }

    // Fingers
    {
        const auto loc_hidefingers = std::find_if(_FingerHiddingKeywords.begin(),_FingerHiddingKeywords.end(),[a_actor](const std::string& a_kw)
        {
            return LibFunctions::GetSingleton()->WornHasKeyword(a_actor,a_kw);
        });
        if (loc_hidefingers != _FingerHiddingKeywords.end()) HideArmNodes(a_actor,_fingerhiddenstates,_FingerNodes);
        else ShowArmNodes(a_actor,_fingerhiddenstates,_FingerNodes);
    }
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
    static bool loc_hidearms = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArms",false);
    if (loc_hidearms)
    {
        UpdateArms(a_actor);
    }
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

    const bool loc_nodehider = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bEnabled",true);
    if (loc_nodehider)
    {
        bool loc_hidearms = ConfigManager::GetSingleton()->GetVariable<bool>("NodeHider.bHideArms",false);
        if (loc_hidearms)
        {
            for (auto&& [handle,state] : _armhiddenstates)
            {
                auto loc_actor = RE::Actor::LookupByHandle(handle);
                if (loc_actor != nullptr)
                {
                    ShowArmNodes(loc_actor.get(),_armhiddenstates,_ArmNodes);
                }
            }
            for (auto&& [handle,state] : _handhiddenstates)
            {
                auto loc_actor = RE::Actor::LookupByHandle(handle);
                if (loc_actor != nullptr)
                {
                    ShowArmNodes(loc_actor.get(),_handhiddenstates,_HandNodes);
                }
            }
            for (auto&& [handle,state] : _fingerhiddenstates)
            {
                auto loc_actor = RE::Actor::LookupByHandle(handle);
                if (loc_actor != nullptr)
                {
                    ShowArmNodes(loc_actor.get(),_fingerhiddenstates,_FingerNodes);
                }
            }
        }

        for (auto&& [handle,state] : _weaponhiddenstates)
        {
            auto loc_actor = RE::Actor::LookupByHandle(handle);
            if (loc_actor != nullptr)
            {
                ShowWeapons(loc_actor.get());
            }
        }
    }
    _UpdatedActors.clear();
    _lastupdatestack.clear();
    _armhiddenstates.clear();
    _handhiddenstates.clear();
    _fingerhiddenstates.clear();
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