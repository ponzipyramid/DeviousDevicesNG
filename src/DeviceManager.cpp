#include "DeviceManager.h"
#include "Script.hpp"
#include "UI.h"

#include <algorithm>
#include <atomic>
#include <unordered_map>
#include <vector>

using namespace DeviousDevices;

DeviceManager& DeviceManager::GetSingleton() noexcept {
    static DeviceManager instance;
    return instance;
}

void DeviceManager::Setup() {
    RE::FormID zadInventoryKwdId = 0x02B5F0;
    RE::TESDataHandler* handler = RE::TESDataHandler::GetSingleton();
    RE::BGSKeyword* kwd = handler->LookupForm<RE::BGSKeyword>(zadInventoryKwdId, "Devious Devices - Integration.esm");
    invDeviceKwds.push_back(kwd);

    // create inventory-rendered device mapping
}

void DeviceManager::ShowEquipMenu(std::function<void(unsigned int)> callback) {
    std::string bodyText = "Do you want to lock this device on yourself?";
    std::vector<std::string> buttonTexts;

    buttonTexts.push_back("Yes");
    buttonTexts.push_back("No");

    DeviousDevices::MessageBox::Show(bodyText, buttonTexts, callback);
}

ScriptUtils::ObjectPtr GetDeviceScript(RE::TESForm* device) { 
    std::string scriptNames[] = {"zadEquipScript", "zadCollarScript", "zadGagScript", "zadBodyHarnessScript", "zadPiercingNippleScript"};
    ScriptUtils::ObjectPtr scriptPtr = nullptr;
    for (const auto& sName : scriptNames) {
        SKSE::log::info("Looking for script {}", sName);
        scriptPtr = ScriptUtils::GetScriptObject(device, sName.c_str());
        if (scriptPtr != nullptr) break;
    }
    return scriptPtr;
}

bool DeviceManager::EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device) {
    ScriptUtils::ObjectPtr deviceScript = GetDeviceScript(device);

    RE::TESObjectARMO* rendered;
    if (deviceScript != nullptr) {
        SKSE::log::info("Found the script - pulling out device");
        rendered = ScriptUtils::GetProperty<RE::TESObjectARMO*>(deviceScript, "deviceRendered");
    } else {
        SKSE::log::info("Could not find equip script");
        rendered = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(
            0x0866B9, "Devious Devices - Integration.esm");
    } 
    
    if (rendered != nullptr) {
        SKSE::log::info("Found rendered device - equipping");
        return actor->AddWornItem(rendered, 1, false, 0, 0);
    } else
        return false;
}