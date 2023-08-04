#pragma once

#include <articuno/articuno.h>
#include <articuno/types/auto.h>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

namespace DeviousDevices {
    class Device;

    class DeviceInfo {
        std::string editorId;
        RE::FormID formId;
        std::string espName;

        articuno_deserialize(ar) { 
            ar <=> articuno::kv(formId, "formId");
            ar <=> articuno::kv(espName, "espName");
            ar <=> articuno::kv(editorId, "editorId");
        }
        
        friend class Device;
        friend class articuno::access;
    };

    class Device : DeviceInfo {
    public:
        inline void Init(RE::TESDataHandler* handler) { 
            inventory = handler->LookupForm<RE::TESObjectARMO>(formId, espName);
            rendered = handler->LookupForm<RE::TESObjectARMO>(renderedInfo.formId, renderedInfo.espName);

            if (!inventory)
                SKSE::log::info("{} inventory device not found", editorId);
            else
                formId = inventory->GetFormID();
            if (!rendered) SKSE::log::info("{} rendered device not found", editorId);

        }
        inline RE::TESObjectARMO* GetRenderedDevice() { return rendered; }
        inline std::string GetName() { return editorId; }
        inline RE::FormID GetFormID() { return inventory->GetFormID(); }
    private:
        articuno_deserialize(ar) {
            ar <=> articuno::kv(formId, "formId");
            ar <=> articuno::kv(espName, "espName");
            ar <=> articuno::kv(editorId, "editorId");

            ar <=> articuno::kv(renderedInfo, "rendered");

        }
        DeviceInfo renderedInfo;
        RE::TESObjectARMO* rendered;
        RE::TESObjectARMO* inventory;

        friend class articuno::access;
    };
}