#pragma once

namespace DeviousDevices {
    class DeviceManager {
    public:
        [[nodiscard]] static DeviceManager& GetSingleton() noexcept;
        
        void Setup();
        
        inline bool IsInventoryDevice(RE::TESForm* obj) { return obj->HasKeywordInArray(invDeviceKwds, true); }

        bool EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device);

        void ShowEquipMenu(std::function<void(unsigned int)> callback);

    private:
        std::vector<RE::BGSKeyword*> invDeviceKwds;
        std::unordered_map<RE::TESForm*, RE::TESForm*> deviceMapping;
    };
}