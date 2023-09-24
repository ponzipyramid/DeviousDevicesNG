#pragma once

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

        std::string _has;
        std::string _kwd;

    };

    struct ConflictMap {
        std::string type;
        std::vector<Conflict> conflicts;

        inline void Init() {
            for (auto conflict : conflicts) conflict.Init();
        }


    };
}