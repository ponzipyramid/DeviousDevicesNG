#include "NodeHider.h"

DeviousDevices::NodeHider* DeviousDevices::NodeHider::_this = new DeviousDevices::NodeHider;

DeviousDevices::NodeHider* DeviousDevices::NodeHider::GetSingleton()
{
    return _this;
}

void DeviousDevices::NodeHider::HideArms()
{
    RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton();
    RE::NiNode* thirdpersonNode = loc_player->Get3D(0)->AsNode();
    RE::NiNode* leftarmNode     = thirdpersonNode->GetObjectByName("NPC L UpperArm [LUar]")->AsNode();
    RE::NiNode* rightarmNode    = thirdpersonNode->GetObjectByName("NPC R UpperArm [RUar]")->AsNode();

    leftarmNode->local.scale  = 0.002f;
    rightarmNode->local.scale = 0.002f;
}

void DeviousDevices::NodeHider::ShowArms()
{
    RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton();
    RE::NiNode* thirdpersonNode = loc_player->Get3D(0)->AsNode();
    RE::NiNode* leftarmNode     = thirdpersonNode->GetObjectByName("NPC L UpperArm [LUar]")->AsNode();
    RE::NiNode* rightarmNode    = thirdpersonNode->GetObjectByName("NPC R UpperArm [RUar]")->AsNode();

    leftarmNode->local.scale  = 1.000f;
    rightarmNode->local.scale = 1.000f;
}

void DeviousDevices::NodeHider::Setup()
{
}
