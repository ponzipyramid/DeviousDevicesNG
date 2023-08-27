#pragma once

#include "Script.hpp"

namespace DeviousDevices {
    class Settings {
    public:
        [[nodiscard]] inline static Settings& GetSingleton() noexcept { 
            static Settings set;
            return set;
        }

        template <typename T>
        inline T GetSetting(std::string name) {
            auto configQuest = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESQuest>(
                0x01A282, "Devious Devices - Integration.esm");
            auto settings = ScriptUtils::GetScriptObject(configQuest, "zadconfig");
            return ScriptUtils::GetProperty<T>(settings, name);
        }

        template <typename T>
        inline T GetDefault(std::string name) {
            auto libQuest = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESQuest>(
                0x00F624, "Devious Devices - Integration.esm");
            auto lib = ScriptUtils::GetScriptObject(libQuest, "zadlibs");
            return ScriptUtils::GetProperty<T>(lib, name);
        }
    };
}


