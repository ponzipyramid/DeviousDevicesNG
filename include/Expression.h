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

    enum BlockCheckMode : uint8_t
    {
        mSet    = 0,
        mReset  = 1
    };

    class ExpressionManager
    {
    SINGLETONHEADER(ExpressionManager)
    public:
        void                Setup();
        bool                ApplyExpression(RE::Actor* a_actor, const std::vector<float> &a_expression, float a_strength, bool a_openMouth,int a_priority);
        std::vector<float>  ApplyExpressionRaw(RE::Actor* a_actor, const std::vector<float> &a_expression);
        std::vector<float>  GetExpression(RE::Actor* a_actor);
        bool                ResetExpression(RE::Actor* a_actor, int a_priority);
        void                UpdateGagExpression(RE::Actor* a_actor);
        void                ResetGagExpression(RE::Actor* a_actor);
        bool                RegisterGagType(RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        bool                RegisterDefaultGagType(std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        int                 UpdateGagExpForNPCs();

    private:
        bool                    _installed = false;
        std::vector<GagType>    _GagTypes;
        GagType                 _DefaultGagType;
        RE::TESFaction*         _BlockFaction;

    private:
        std::vector<float>  GetGagEffectPreset(RE::Actor* a_actor);
        void                ApplyPhonemsFaction(RE::Actor* a_actor, std::vector<float>& a_exp, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        std::vector<float>  FactionsToPreset(RE::Actor* a_actor, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults);
        bool                IsGagged(RE::Actor* a_actor) const;
        void                ApplyGagExpression(RE::Actor* a_actor, const std::vector<float> &a_expression);
        std::vector<float>  ApplyStrengthToExpression(const std::vector<float>& a_expression,float a_strength);
        bool                CheckExpressionBlock(RE::Actor* a_actor, int a_priority, BlockCheckMode a_mode);

    };


    inline bool ApplyExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<float> a_expression,int a_strength, bool a_openMouth,int a_priority)
    {
        return ExpressionManager::GetSingleton()->ApplyExpression(a_actor, a_expression,a_strength/100.0f,a_openMouth,a_priority);
    }
    inline std::vector<float> GetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
    {
        return ExpressionManager::GetSingleton()->GetExpression(a_actor);
    }
    inline void ResetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, int a_priority)
    {
        ExpressionManager::GetSingleton()->ResetExpression(a_actor,a_priority);
    }
    inline void UpdateGagExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
    {
        ExpressionManager::GetSingleton()->UpdateGagExpression(a_actor);
    }
    inline bool RegisterGagType(PAPYRUSFUNCHANDLE, RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        return ExpressionManager::GetSingleton()->RegisterGagType(a_keyword,a_factions,a_defaults);
    }
    inline bool RegisterDefaultGagType(PAPYRUSFUNCHANDLE, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        return ExpressionManager::GetSingleton()->RegisterDefaultGagType(a_factions,a_defaults);
    }
    inline void ResetGagExpression(PAPYRUSFUNCHANDLE,RE::Actor* a_actor)
    {
        ExpressionManager::GetSingleton()->ResetGagExpression(a_actor);
    }


}