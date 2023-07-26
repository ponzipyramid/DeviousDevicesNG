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

    std::erase_if(buttonTexts, [](const std::string& text) { return text.empty(); });
    int messageBoxId = 1;
    DeviousDevices::MessageBox::Show(bodyText, buttonTexts, callback);
}

void DeviceManager::EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device) {
    RE::TESObjectARMO* rendered = RE::TESDataHandler::GetSingleton()->LookupForm<RE::TESObjectARMO>(
        0x0866B9, "Devious Devices - Integration.esm");
    
    if (rendered != nullptr) {
        SKSE::log::info("Found rendered device - equipping");
        actor->AddWornItem(rendered, 1, false, 0, 0);
    } else
        SKSE::log::info("Could not find rendered device");
}