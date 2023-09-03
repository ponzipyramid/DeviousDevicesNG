#pragma once

#include <articuno/articuno.h>
#include <articuno/types/auto.h>
#include <SKSE/SKSE.h>

namespace DeviousDevices {
    class Conflict {
    public:
        RE::BGSKeyword* kwd;
        RE::BGSKeyword* has;

        inline void Init() { 
            kwd = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(_kwd);
            has = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(_has);
        }
    private: 
        articuno_serde(ar) {
            ar <=> articuno::kv(_kwd, "kwd");
            ar <=> articuno::kv(_has, "has");
        }

        std::string _has;
        std::string _kwd;

        friend class articuno::access;

    };

    class ConflictMap {
    public:
        std::string type;
        std::vector<Conflict> conflicts;

        inline void Init() {
            for (auto conflict : conflicts) conflict.Init();
        }

    private:
        articuno_serde(ar) {
            ar <=> articuno::kv(type, "type");
            ar <=> articuno::kv(conflicts, "conflicts");
        }

        friend class articuno::access;

    };
}