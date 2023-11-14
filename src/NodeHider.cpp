#include "NodeHider.h"
#include "LibFunctions.h"
#include "Hider.h"

SINGLETONBODY(DeviousDevices::NodeHider)

#ifdef NH_IMPARMHIDER

void DeviousDevices::NodeHider::HideArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0)->AsNode();

    if (thirdpersonNode == nullptr) return;

    RE::NiNode* leftarmNode     = thirdpersonNode->GetObjectByName("NPC L UpperArm [LUar]")->AsNode();
    if (leftarmNode == nullptr) return;

    RE::NiNode* rightarmNode    = thirdpersonNode->GetObjectByName("NPC R UpperArm [RUar]")->AsNode();
    if (rightarmNode == nullptr) return;

    leftarmNode->local.scale  = 0.002f;
    rightarmNode->local.scale = 0.002f;
}

void DeviousDevices::NodeHider::ShowArms(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    RE::NiNode* thirdpersonNode = a_actor->Get3D(0)->AsNode();

    if (thirdpersonNode == nullptr) return;

    RE::NiNode* leftarmNode     = thirdpersonNode->GetObjectByName("NPC L UpperArm [LUar]")->AsNode();
    if (leftarmNode == nullptr) return;

    RE::NiNode* rightarmNode    = thirdpersonNode->GetObjectByName("NPC R UpperArm [RUar]")->AsNode();
    if (rightarmNode == nullptr) return;

    leftarmNode->local.scale  = 1.000f;
    rightarmNode->local.scale = 1.000f;
}

#endif

void DeviousDevices::NodeHider::HideWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    //LOG("HideWeapons called for {}",a_actor->GetName());

    for (auto&& it : WeaponNodes)
    {
        AddHideNode(a_actor,it);
    }
}



void DeviousDevices::NodeHider::ShowWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    //LOG("ShowWeapons called for {}",a_actor->GetName());

    for (auto&& it : WeaponNodes)
    {
        RemoveHideNode(a_actor,it);
    }
}

void DeviousDevices::NodeHider::Setup()
{ 
    if (!_installed)
    {
        LOG("NodeHider::Setup() - Installed")
        _installed = true;
    }
}

void DeviousDevices::NodeHider::Update()
{
    LOG("NodeHider::Update() - Updating...")

    static RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton(); 

    std::vector<RE::Actor*> loc_lastactors;
    std::vector<RE::Actor*> loc_currentactors;

    for (auto&& it : _lastupdatestack)
    {
        loc_lastactors.push_back(RE::Actor::LookupByHandle(it).get());
    }

    uint16_t loc_updated = 0;
    RE::TES::GetSingleton()->ForEachReferenceInRange(loc_player, 3000, [&](RE::TESObjectREFR& a_ref) {
        auto loc_refBase    = a_ref.GetBaseObject();
        auto loc_actor      = a_ref.As<RE::Actor>();
        if (ShouldHideWeapons(loc_actor) && (a_ref.Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC)))) 
        {
            loc_updated += 1;
            loc_currentactors.push_back(loc_actor);
            //UpdateGagExpression(loc_actor);

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

    LOG("NodeHider::Update() - loc_currentactors = {}",loc_currentactors.size())
    LOG("NodeHider::Update() - loc_lastactors = {}",loc_lastactors.size())
    LOG("NodeHider::Update() - loc_samectors = {}",loc_samectors.size())
    LOG("NodeHider::Update() - loc_addedactors = {}",loc_addedactors.size())
    LOG("NodeHider::Update() - loc_removedactors = {}",loc_removedactors.size())

    //remove weapon node hider from removed actors
    for (auto&& it : loc_removedactors)
    {
        ShowWeapons(it);
    }

    //hide weapons for same actors, so it stay hidden
    for (auto&& it : loc_samectors)
    {
        HideWeapons(it);
    }

    //hide weapons for added actors
    for (auto&& it : loc_addedactors)
    {
        HideWeapons(it);
        //DeviceHiderManager::GetSingleton()->Update3DSafe(it);
    }

    //update last actors
    _lastupdatestack.clear();
    for(auto&& it : loc_currentactors)
    {
        _lastupdatestack.push_back(it->GetHandle().native_handle());
    }

    LOG("NodeHider::Update() - Node hider updated {} actors",loc_updated)
}

bool DeviousDevices::NodeHider::ActorIsValid(RE::Actor* a_actor) const
{
    if (a_actor == nullptr) return false;
    
    if (a_actor->IsDead() || !a_actor->Is3DLoaded() || a_actor->IsDisabled() || (a_actor->GetFormID() == 0))
    {
        return false;
    }
    return true;
}

bool DeviousDevices::NodeHider::ShouldHideWeapons(RE::Actor* a_actor) const
{
    if (!ActorIsValid(a_actor)) return false;
    return LibFunctions::GetSingleton()->IsAnimating(a_actor) || (LibFunctions::GetSingleton()->GetHandRestrain(a_actor) != nullptr);
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