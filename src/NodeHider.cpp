#include "NodeHider.h"

DeviousDevices::NodeHider* DeviousDevices::NodeHider::_this = new DeviousDevices::NodeHider;

DeviousDevices::NodeHider* DeviousDevices::NodeHider::GetSingleton()
{
    return _this;
}

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

void DeviousDevices::NodeHider::HideWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    SKSE::log::info("HideWeapons called for {}",a_actor->GetName());

    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(0)->AsNode();

    if (loc_thirdpersonNode == nullptr) return;

    RE::NiAVObject* loc_bownode         = loc_thirdpersonNode->GetObjectByName("WeaponBow");
    RE::NiAVObject* loc_quivernode      = loc_thirdpersonNode->GetObjectByName("QUIVER");
    RE::NiAVObject* loc_weaponbacknode  = loc_thirdpersonNode->GetObjectByName("WeaponBack");
    
    if (loc_bownode != nullptr)         loc_bownode->AsNode()->local.scale          = 0.002f;
    if (loc_quivernode != nullptr)      loc_quivernode->AsNode()->local.scale       = 0.002f;
    if (loc_weaponbacknode != nullptr)  loc_weaponbacknode->AsNode()->local.scale   = 0.002f;
}

void DeviousDevices::NodeHider::ShowWeapons(RE::Actor* a_actor)
{
    if (a_actor == nullptr) return;

    SKSE::log::info("ShowWeapons called for {}",a_actor->GetName());

    RE::NiNode* loc_thirdpersonNode = a_actor->Get3D(0)->AsNode();

    if (loc_thirdpersonNode == nullptr) return;

    RE::NiAVObject* loc_bownode         = loc_thirdpersonNode->GetObjectByName("WeaponBow");
    RE::NiAVObject* loc_quivernode      = loc_thirdpersonNode->GetObjectByName("QUIVER");
    RE::NiAVObject* loc_weaponbacknode  = loc_thirdpersonNode->GetObjectByName("WeaponBack");
    
    if (loc_bownode != nullptr)         loc_bownode->AsNode()->local.scale          = 1.000f;
    if (loc_quivernode != nullptr)      loc_quivernode->AsNode()->local.scale       = 1.000f;
    if (loc_weaponbacknode != nullptr)  loc_weaponbacknode->AsNode()->local.scale   = 1.000f;
}

void DeviousDevices::NodeHider::Setup()
{
}

void DeviousDevices::HideWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
{
    NodeHider::GetSingleton()->HideWeapons(a_actor);
}

void DeviousDevices::ShowWeapons(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
{
    NodeHider::GetSingleton()->ShowWeapons(a_actor);
}