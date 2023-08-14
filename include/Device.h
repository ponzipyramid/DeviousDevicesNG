#pragma once

#include <articuno/articuno.h>
#include <articuno/types/auto.h>

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

namespace DeviousDevices {
    class Device;

    class FormInfo {
    public:
        template <class T>
        inline T* GetForm(RE::TESDataHandler* handler) {
            return handler->LookupForm<T>(formId, espName);
        }

    private:

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

    class KeywordListWrapper : FormInfo {
    public: 
        inline void Init(RE::TESDataHandler* handler) { 
            kwds.clear();
            for (auto& info : infos) {
                kwds.push_back(info.GetForm<RE::BGSKeyword>(handler));
            }
        }
        inline std::vector<RE::BGSKeyword*> GetKwds() { return kwds; }

        std::vector<FormInfo> infos;
    private:
        std::vector<RE::BGSKeyword*> kwds;
    };

    class Device : FormInfo {
    public:
        void Init(RE::TESDataHandler* handler);
        bool CanEquip(RE::Actor* actor);

        inline RE::TESObjectARMO* GetRenderedDevice() { return rendered; }
        inline RE::BGSMessage* GetEquipMenu() { return equipMenu; }
        inline std::string GetName() { return editorId; }
        inline RE::FormID GetFormID() { return inventory->GetFormID(); }
    private:
        articuno_deserialize(ar) {
            ar <=> articuno::kv(formId, "formId");
            ar <=> articuno::kv(espName, "espName");
            ar <=> articuno::kv(editorId, "editorId");

            ar <=> articuno::kv(equipConflictingDeviceKwds.infos, "equipConflictingDeviceKwds");
            ar <=> articuno::kv(requiredDeviceKwds.infos, "requiredDeviceKwds");
            ar <=> articuno::kv(unequipConflictingDeviceKwds.infos, "unequipConflictingDeviceKwds");

            ar <=> articuno::kv(kwdInfo, "kwd");

            ar <=> articuno::kv(renderedInfo, "rendered");
            ar <=> articuno::kv(equipMenuInfo, "equipMenu");
        }
        FormInfo renderedInfo;

        FormInfo kwdInfo;
        RE::BGSKeyword* kwd;

        RE::TESObjectARMO* rendered;
        RE::TESObjectARMO* inventory;

        KeywordListWrapper equipConflictingDeviceKwds;
        KeywordListWrapper requiredDeviceKwds;
        KeywordListWrapper unequipConflictingDeviceKwds;

        FormInfo equipMenuInfo;
        RE::BGSMessage* equipMenu;

        friend class articuno::access;
    };
}