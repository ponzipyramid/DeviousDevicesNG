#include "DeviceManager.h"
#include "DeviceReader.h"
#include "UI.h"

#include <algorithm>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <SKSE/SKSE.h>
#include <articuno/archives/ryml/ryml.h>
#include <chrono>

using namespace DeviousDevices;
using namespace SKSE;
using namespace articuno::ryml;

DeviceManager& DeviceManager::GetSingleton() noexcept {
    static DeviceManager instance;
    return instance;
}



void DeviceManager::Setup() {
    RE::FormID zadInventoryKwdId = 0x02B5F0;
    RE::TESDataHandler* handler = RE::TESDataHandler::GetSingleton();
    RE::BGSKeyword* kwd = handler->LookupForm<RE::BGSKeyword>(zadInventoryKwdId, "Devious Devices - Integration.esm");
    invDeviceKwds.push_back(kwd);
}

bool DeviceManager::CanEquipDevice(RE::Actor* actor, RE::TESForm* item) {
    RE::FormID formId = item->GetFormID();

    if (devices.count(formId)) {

        return devices[formId].CanEquip(actor);
    } else {
        return false;
    }
}

void DeviceManager::ShowEquipMenu(RE::TESForm* item, std::function<void(bool)> callback) {
    if (!devices.count(item->GetFormID())) return;

    RE::BGSMessage* equipMenu = devices[item->GetFormID()].GetEquipMenu();

    if (equipMenu != nullptr)
        DeviousDevices::MessageBox::Show(equipMenu, [callback](uint32_t result) { callback(result == 0); });
    else
        SKSE::log::info("Could not fetch message box for {}", item->GetFormID());
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