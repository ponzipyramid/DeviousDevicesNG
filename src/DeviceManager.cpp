#include "DeviceManager.h"
#include "UI.h"

#include <algorithm>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <SKSE/SKSE.h>
#include <articuno/archives/ryml/ryml.h>

using namespace DeviousDevices;
using namespace SKSE;
using namespace articuno::ryml;

DeviceManager& DeviceManager::GetSingleton() noexcept {
    static DeviceManager instance;
    return instance;
}

void DeviceManager::LoadConfig() { 
    std::string base("Data\\SKSE\\Plugins\\Devious Devices NG"); 


    std::ifstream devicesFile(base + "\\devices.json");
    if (devicesFile.good()) {
        yaml_source ar(devicesFile);

        ar >> deviceList;


    } else
        log::error("Error: Failed to read devices file");
}

void DeviceManager::Setup() {
    RE::FormID zadInventoryKwdId = 0x02B5F0;
    RE::TESDataHandler* handler = RE::TESDataHandler::GetSingleton();
    RE::BGSKeyword* kwd = handler->LookupForm<RE::BGSKeyword>(zadInventoryKwdId, "Devious Devices - Integration.esm");
    invDeviceKwds.push_back(kwd);

    for (auto& device : deviceList) {
        device.Init(handler);
        devices[device.GetFormID()] = device;
    }
}

void DeviceManager::ShowEquipMenu(std::function<void(unsigned int)> callback) {
    std::string bodyText = "Do you want to lock this device on yourself?";
    std::vector<std::string> buttonTexts;

    buttonTexts.push_back("Yes");
    buttonTexts.push_back("No");

    DeviousDevices::MessageBox::Show(bodyText, buttonTexts, callback);
}

bool DeviceManager::EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device) {
    if (devices.count(device->GetFormID())) {
        RE::TESObjectARMO* rendered = devices[device->GetFormID()].GetRenderedDevice();

        if (rendered != nullptr) {
            return actor->AddWornItem(rendered, 1, false, 0, 0);
        } else {
            SKSE::log::info("Cound not find rendered device");
            return false;
        }
    } else {
        SKSE::log::info("Could not find device {} {} {} in registry", device->GetFormID(), device->GetRawFormID(), device->GetLocalFormID());
        return false;
    }
}