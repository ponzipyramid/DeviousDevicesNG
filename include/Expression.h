#pragma once
#include <RE/Skyrim.h>

namespace DeviousDevices 
{
    struct GagType
    {
        RE::BGSKeyword*                 keyword;
        std::vector<RE::TESFaction*>    factions;
        std::vector<int>                defaults;
    };

    class ExpressionManager
    {
    SINGLETONHEADER(ExpressionManager)
    public:
        void Setup();
        std::vector<float> ApplyExpression(RE::Actor* a_actor, const std::vector<float> &a_expression);
        std::vector<float> GetExpression(RE::Actor* a_actor);
        void ResetExpression(RE::Actor* a_actor, bool a_phonem, bool b_mods);
        void UpdateGagExpression(RE::Actor* a_actor);
        bool RegisterGagType(RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        bool RegisterDefaultGagType(std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        std::vector<float> ApplyStrengthToExpression(const std::vector<float>& a_expression,int a_strength);

        int UpdateGagExpForNPCs();

    private:
        bool _installed = false;
        std::vector<GagType> _GagTypes;
        GagType _DefaultGagType;
        std::vector<float> GetGagEffectPreset(RE::Actor* a_actor);
        void ApplyPhonemsFaction(RE::Actor* a_actor, std::vector<float>& a_exp, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        std::vector<float> FactionsToPreset(RE::Actor* a_actor, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);

        bool IsGagged(RE::Actor* a_actor) const;
        void ApplyGagExpression(RE::Actor* a_actor, const std::vector<float> &a_expression);
    };


    inline std::vector<float> ApplyExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<float> a_expression)
    {
        return ExpressionManager::GetSingleton()->ApplyExpression(a_actor, a_expression);
    }
    inline std::vector<float> GetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
    {
        return ExpressionManager::GetSingleton()->GetExpression(a_actor);
    }
    inline void ResetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, bool a_phonem, bool b_mods)
    {
        ExpressionManager::GetSingleton()->ResetExpression(a_actor,a_phonem,b_mods);
    }
    inline void UpdateGagExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
    {
        ExpressionManager::GetSingleton()->UpdateGagExpression(a_actor);
    }
    inline std::vector<float> ApplyStrengthToExpression(PAPYRUSFUNCHANDLE, std::vector<float> a_expression, int a_strength)
    {
        return ExpressionManager::GetSingleton()->ApplyStrengthToExpression(a_expression,a_strength);
    }
    inline bool RegisterGagType(PAPYRUSFUNCHANDLE, RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        return ExpressionManager::GetSingleton()->RegisterGagType(a_keyword,a_factions,a_defaults);
    }
    inline bool RegisterDefaultGagType(PAPYRUSFUNCHANDLE, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        return ExpressionManager::GetSingleton()->RegisterDefaultGagType(a_factions,a_defaults);
    }
    

}