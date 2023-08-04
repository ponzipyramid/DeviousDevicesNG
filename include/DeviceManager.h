#pragma once

#include "Device.h"

namespace DeviousDevices {
    class DeviceManager {
    public:
        [[nodiscard]] static DeviceManager& GetSingleton() noexcept;
        
        void LoadConfig();

        void Setup();
        
        inline bool IsInventoryDevice(RE::TESForm* obj) { return obj->HasKeywordInArray(invDeviceKwds, true); } // might be faster to check if in devices

        bool EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device);

        void ShowEquipMenu(std::function<void(unsigned int)> callback);

    private:
        std::vector<RE::BGSKeyword*> invDeviceKwds;
        std::unordered_map<RE::FormID, Device> devices;
        std::vector<Device> deviceList;
    };
}