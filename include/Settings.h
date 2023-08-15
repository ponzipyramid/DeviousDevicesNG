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
            ptr = ScriptUtils::GetScriptObject(quest, "zadconfig");
        }

        template <typename T>
        inline T GetSetting(std::string name) {
            LOG("Ptr is {}", ptr != nullptr);
            return ScriptUtils::GetProperty<T>(ptr, name);
        }

    private:
        ScriptUtils::ObjectPtr ptr;
    };
}


