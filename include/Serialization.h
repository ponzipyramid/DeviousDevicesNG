#pragma once

namespace DeviousDevices
{
    void OnGameLoaded(SKSE::SerializationInterface* a_serde);
    void OnGameSaved(SKSE::SerializationInterface* a_serde);
    void OnRevert(SKSE::SerializationInterface* a_serde);
}