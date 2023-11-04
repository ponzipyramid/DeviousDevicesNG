#include "NodeHider.h"

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

    if (_slots.find(a_actor) == _slots.end())
    {
        //LOG("Actor {} have no hiden nodes",a_actor->GetName());
        return;
    }

    for (auto&& it : WeaponNodes)
    {
        RemoveHideNode(a_actor,it);
    }
}

void DeviousDevices::NodeHider::Setup()
{ 
}

void DeviousDevices::NodeHider::Update(const float& a_delta)
{
    for (auto&& it : _slots)
    {
        RE::Actor* loc_actor = it.first;
        if (ValidateActor(loc_actor))
        {
            if (loc_actor->Is3DLoaded())
            {
                NodeHiderSlot* loc_slot = &it.second;
                if (loc_slot->enabled)
                {
                    loc_slot->timer += a_delta;
    
                    if (loc_slot->timer >= NH_UPDTIME)
                    {
                        loc_slot->timer = 0.0f;
                        if (loc_slot->nodes.size() > 0)
                        {
                            for (auto&& it : loc_slot->nodes)
                            {
                                it->local.scale = 0.002f;
                            }
                        }
                        else
                        {
                            //no nodes, unregister npc to save resources
                            _slots.erase(loc_actor);
                            //LOG("Update({},{}) - Actor have no more nodes to hide, unregistering, new size={})",loc_actor->GetName(),a_delta,_slots.size())
                        }
                    }
                }
            }
        }
    }
}

bool DeviousDevices::NodeHider::ValidateActor(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return false;
    
    bool loc_unregister = false;

    if (!loc_unregister && (a_actor == nullptr)) loc_unregister = true;
    if (!loc_unregister && a_actor->IsDead())    loc_unregister = true;

    if (loc_unregister)
    {
        _slots.erase(a_actor);
    }
    return !loc_unregister;
}

bool DeviousDevices::NodeHider::AddHideNode(RE::Actor* a_actor, std::string a_nodename)
{
    if (a_actor == nullptr) return false;

    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(false)->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;

    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    if (loc_node != nullptr)
    {
        if (std::find(_slots[a_actor].nodes.begin(),_slots[a_actor].nodes.end(), loc_node->AsNode()) == _slots[a_actor].nodes.end())
        {
            _slots[a_actor].nodes.push_back(loc_node->AsNode());
            //LOG("AddHideNode({},{})",a_actor->GetName(),a_nodename);
            return true;
        }
        else
        {
            //LOG("AddHideNode({},{}) - Node already present, skipping",a_actor->GetName(),a_nodename);
            return false;
        }
    }
    return false;
}

bool DeviousDevices::NodeHider::RemoveHideNode(RE::Actor* a_actor, std::string a_nodename)
{
    if (a_actor == nullptr) return false;

    if (_slots.find(a_actor) == _slots.end())
    {
        LOG("Actor {} have no hiden nodes",a_actor->GetName());
        return false;
    }

    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(false)->AsNode();
    
    if (loc_thirdpersonNode == nullptr) return false;

    RE::NiAVObject* loc_node = loc_thirdpersonNode->GetObjectByName(a_nodename);
    if (loc_node != nullptr)
    {
        if (std::find(_slots[a_actor].nodes.begin(),_slots[a_actor].nodes.end(), loc_node->AsNode()) != _slots[a_actor].nodes.end())
        {
            _slots[a_actor].nodes.erase(std::find(_slots[a_actor].nodes.begin(),_slots[a_actor].nodes.end(), loc_node->AsNode()));
            loc_node->AsNode()->local.scale = 1.00f;
            return true;
        }
    }
    return false;
}

void DeviousDevices::HideWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
{
    NodeHider::GetSingleton()->HideWeapons(a_actor);
}

void DeviousDevices::ShowWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
{
    NodeHider::GetSingleton()->ShowWeapons(a_actor);
}

bool DeviousDevices::NodeHider::NodeHiderSlot::operator==(const NodeHiderSlot& a_other)
{
    return (std::memcmp(this,&a_other,sizeof(NodeHiderSlot)) == 0);
}
