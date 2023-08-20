#pragma once

#include "Script.hpp"

namespace DeviousDevices {
    class Settings {
    public:
        [[nodiscard]] inline static Settings& GetSingleton() noexcept { 
            static Settings set;
            return set;
        }

        inline void Setup() {
            auto quest = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESQuest>(
                0x01A282, "Devious Devices - Integration.esm");
            settings = ScriptUtils::GetScriptObject(quest, "zadconfig");

            quest = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESQuest>(0x00F624,
                                                                                 "Devious Devices - Integration.esm");
            lib = ScriptUtils::GetScriptObject(quest, "zadlibs");
        }

        template <typename T>
        inline T GetSetting(std::string name) {
            return ScriptUtils::GetProperty<T>(settings, name);
        }

        template <typename T>
        inline T GetDefault(std::string name) {
            return ScriptUtils::GetProperty<T>(lib, name);
        }

    private:
        ScriptUtils::ObjectPtr settings;
        ScriptUtils::ObjectPtr lib;
    };
}


