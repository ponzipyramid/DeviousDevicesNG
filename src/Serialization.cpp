#include "Serialization.h"
#include "NodeHider.h"
#include "Hider.h"
#include "Expression.h"

void DeviousDevices::OnGameLoaded(SKSE::SerializationInterface* a_serde)
{
    LOG("DeviousDevices::OnGameLoaded called")
}

void DeviousDevices::OnGameSaved(SKSE::SerializationInterface* a_serde)
{
    LOG("DeviousDevices::OnGameSaved called")
}

void DeviousDevices::OnRevert(SKSE::SerializationInterface* a_serde)
{
    LOG("DeviousDevices::OnRevert called")
    NodeHider::GetSingleton()->Reload();
    DeviceHiderManager::GetSingleton()->Reload();
    ExpressionManager::GetSingleton()->Reload();
}
