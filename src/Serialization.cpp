#include "Serialization.h"
#include "NodeHider.h"

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
}
