#include "Expression.h"
#include "Config.h"
#include "Utils.h"
#include "LibFunctions.h"

SINGLETONBODY(DeviousDevices::ExpressionManager)

namespace DeviousDevices
{
    void ExpressionManager::Setup()
    {
        if (!_installed)
        {
            _installed = true;
            RE::TESDataHandler* loc_datahandler = RE::TESDataHandler::GetSingleton();
            if (loc_datahandler)
            {
                _BlockFaction = reinterpret_cast<RE::TESFaction*>(loc_datahandler->LookupForm(0x000811, "Devious Devices - Integration.esm"));
            }
            else
            {
                WARN("ExpressionManager::Setup() - Could not load block faction!")
            }
        }
    }

    bool ExpressionManager::ApplyExpression(RE::Actor* a_actor, const std::vector<float> &a_expression, float a_strength, bool a_openMouth,int a_priority)
    {
        LOG("ApplyExpression({},{},{},{}) called",a_actor ? a_actor->GetName() : "NONE",a_strength,a_openMouth,a_priority)

        if (a_actor == nullptr || !a_actor->Is3DLoaded())
        {
            WARN("ExpressionManager::ApplyExpression - Actor is none, or not loaded")
            return false;
        }

        if (a_expression.size() != 32)
        {
            ERROR("ExpressionManager::ApplyExpression - Expression size have to be 32!")
            return false;
        }

        //validate values
        a_strength = std::clamp(a_strength,0.0f,100.0f);
        a_priority = std::clamp(a_priority,0,100);

        if (CheckExpressionBlock(a_actor,a_priority,mSet))
        {
            std::vector<float> loc_exp = a_expression;
            if (a_openMouth) loc_exp[0] = 0.75f;

            loc_exp = ApplyStrengthToExpression(loc_exp,a_strength);
            ApplyExpressionRaw(a_actor, loc_exp);
            return true;
        }
        else
        {
            return false;
        }
    }

    std::vector<float> ExpressionManager::ApplyExpressionRaw(RE::Actor* a_actor, const std::vector<float> &a_expression)
    {
        LOG("ApplyExpressionRaw({}) called",a_actor ? a_actor->GetName() : "NONE")

        if (a_actor == nullptr) return std::vector<float>();

        if (a_expression.size() != 32) 
        {
            ERROR("Expression is of incorrect size - returning")
            return GetExpression(a_actor);
        }
        std::vector<float> loc_expression = GetExpression(a_actor);

        //check if its not same
        if (loc_expression == a_expression) 
        {
            //WARN("Expression is same as previous one - returning")
            return loc_expression;
        }

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return std::vector<float>();

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        bool loc_phonems    = !IsGagged(a_actor);
        bool loc_mods       = true;

        //set phonems and modifiers 
        for(int i = 0; i < a_expression.size();i++)
        {
            switch(i)
            {
                //phonems
                case 0:  //Aah    
                case 1:  //BigAah 
                case 2:  //BMP    
                case 3:  //ChJSh  
                case 4:  //DST    
                case 5:  //Eee    
                case 6:  //Eh     
                case 7:  //FV     
                case 8:  //I      
                case 9:  //K      
                case 10: //N      
                case 11: //Oh     
                case 12: //OohQ   
                case 13: //R      
                case 14: //Th     
                case 15: //W      
                    if (loc_phonems) loc_expdata->phenomeKeyFrame.SetValue(i, a_expression[i]);
                    break;
                //modifiers
                case 16: //BlinkLeft    
                case 17: //BlinkRight   
                case 18: //BrowDownLeft 
                case 19: //BrowDownRight
                case 20: //BrowInLeft   
                case 21: //BrowInRight  
                case 22: //BrowUpLeft   
                case 23: //BrowUpRight  
                case 24: //LookDown     
                case 25: //LookLeft     
                case 26: //LookRight    
                case 27: //LookUp       
                case 28: //SquintLeft   
                case 29: //SquintRight  
                    if (loc_mods) loc_expdata->modifierKeyFrame.SetValue(i - 16, a_expression[i]);
                    break;
            }
        }

        //apply expression override
        if (loc_mods)
        {
            if ((loc_expression[30] != a_expression[30]) || (loc_expression[31] != a_expression[31]))
            {
                loc_expdata->exprOverride = false;
                loc_expdata->SetExpressionOverride(std::lround(a_expression[30]),a_expression[31]);
                loc_expdata->exprOverride = true;
                
            }
        }

        return GetExpression(a_actor);
    }

    std::vector<float> ExpressionManager::GetExpression(RE::Actor* a_actor)
    {
        LOG("GetExpression({}) called",a_actor ? a_actor->GetName() : "NONE")

        if (a_actor == nullptr) return std::vector<float>(32,0.0f);

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();
        
        if (loc_expdata == nullptr) return std::vector<float>(32,0.0f);

        std::vector<float> loc_res;

        for (int i = 0; i < 16; i++) loc_res.push_back(loc_expdata->phenomeKeyFrame.values[i]); 
        for (int i = 0; i < 14; i++) loc_res.push_back(loc_expdata->modifierKeyFrame.values[i]);


        bool loc_found = false;
        const size_t loc_count_exp = loc_expdata->expressionKeyFrame.count;
        for (int i = 0; i < loc_count_exp;i++)
        {
            if (loc_expdata->expressionKeyFrame.values[i] != 0.0f)
            {
                loc_res.push_back(i);
                loc_res.push_back(loc_expdata->expressionKeyFrame.values[i]);
                loc_found = true;
                break;
            }
        }

        if (!loc_found)
        {
            //add neutral mood
            loc_res.push_back(7);
            loc_res.push_back(0.5f);
        }


        return loc_res;
    }

    bool ExpressionManager::ResetExpression(RE::Actor* a_actor, int a_priority)
    {
        LOG("ResetExpression({},{}) called",a_actor ? a_actor->GetName() : "NONE",a_priority)

        if (a_actor == nullptr) return false;
        
        if (!CheckExpressionBlock(a_actor,a_priority,mReset)) return false;

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return false;

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        if (!IsGagged(a_actor)) for (int i = 0; i < 16; i++) loc_expdata->phenomeKeyFrame.SetValue(i,0.0f);

        for (int i = 0; i < 14; i++) loc_expdata->modifierKeyFrame.SetValue(i,0.0f);
        a_actor->ClearExpressionOverride();

        return true;
    }

    std::vector<float> ExpressionManager::FactionsToPreset(RE::Actor* a_actor, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        if (a_actor == nullptr) return std::vector<float>(32,0.0f);

        std::vector<float> loc_preset(32,0.0f);

        if (a_factions.size() > 0)
        {
            for(int i =0; i < a_factions.size();i++)
            {
                int loc_rank = std::clamp(a_actor->GetFactionRank(a_factions[i],a_actor->IsPlayer()),-1,100);
                if (loc_rank >= 0)  (loc_preset[i] = loc_rank/100.0f);
                else                (loc_preset[i] = a_defaults[i]/100.0f);
            }
        }
        else
        {
            for(int i =0; i < a_defaults.size();i++)
            {
                loc_preset[i] = std::clamp(a_defaults[i],0,100)/100.0f;
            }
        }
        return loc_preset;
    }

    bool ExpressionManager::IsGagged(RE::Actor* a_actor) const
    {
        if (a_actor == nullptr) return false;
        const RE::TESObjectARMO* loc_gag = LibFunctions::GetSingleton()->GetWornArmor(a_actor,(int)RE::BIPED_MODEL::BipedObjectSlot::kModMouth);
        if (loc_gag == nullptr) return false;

        return loc_gag->HasKeywordString("zad_DeviousGag");
    }

    void ExpressionManager::ApplyGagExpression(RE::Actor* a_actor, const std::vector<float>& a_expression)
    {
        if (a_actor == nullptr) return;

        if (a_expression.size() != 16) 
        {
            ERROR("ExpressionManager::ApplyGagExpression - Expression is of incorrect size - returning")
            return;
        }

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return;

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        //set phonems and modifiers 
        for(int i = 0; i < 16;i++)
        {
            switch(i)
            {
                //phonems
                case 0:  //Aah    
                case 1:  //BigAah 
                case 2:  //BMP    
                case 3:  //ChJSh  
                case 4:  //DST    
                case 5:  //Eee    
                case 6:  //Eh     
                case 7:  //FV     
                case 8:  //I      
                case 9:  //K      
                case 10: //N      
                case 11: //Oh     
                case 12: //OohQ   
                case 13: //R      
                case 14: //Th     
                case 15: //W      
                    loc_expdata->phenomeKeyFrame.SetValue(i, a_expression[i]);
                    break;
            }
        }

        //prevent Combat shout expression as it makes gag looking worse
        if (loc_expdata->phenomeKeyFrame.values[30] == 16) loc_expdata->SetExpressionOverride(16,0);

    }

    bool ExpressionManager::CheckExpressionBlock(RE::Actor* a_actor, int a_priority, BlockCheckMode a_mode)
    {
        if (!a_actor->IsInFaction(_BlockFaction))
        {
            if (a_mode == mSet)
            {
                a_actor->AddToFaction(_BlockFaction,a_priority);
            }
            return true;
        }

        if (a_priority >= a_actor->GetFactionRank(_BlockFaction,a_actor->IsPlayer()))
        {
            if (a_mode == mSet)
            {
                a_actor->AddToFaction(_BlockFaction,a_priority);
                return true;
            }
            else if (a_mode == mReset)
            {
                a_actor->AddToFaction(_BlockFaction,0);
                return true;
            }
        
        }
        return false;
    }

    void ExpressionManager::ApplyPhonemsFaction(RE::Actor* a_actor, std::vector<float>& a_exp, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        if (a_actor == nullptr) return;

        if (a_factions.size() == 16)
        {
            for(int i = 0 ; i < 16;i++)
            {
                int loc_rank = std::clamp(a_actor->GetFactionRank(a_factions[i],a_actor->IsPlayer()),-1,100);
                if (loc_rank >= 0)  (a_exp[i] = loc_rank/100.0f);
                else                (a_exp[i] = a_defaults[i]/100.0f);
            }
        }
        else
        {
            for(int i = 0; i < a_defaults.size();i++)
            {
                a_exp[i] = std::clamp(a_defaults[i],0,100)/100.0f;
            }
        }
    }

    void ExpressionManager::UpdateGagExpression(RE::Actor* a_actor)
    {
        if (a_actor == nullptr) return;

        const std::vector<float> loc_new = GetGagEffectPreset(a_actor);

        ApplyGagExpression(a_actor,loc_new);
    }

    void ExpressionManager::ResetGagExpression(RE::Actor* a_actor)
    {
        if (a_actor == nullptr) return;
        
        if (IsGagged(a_actor)) return;

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return;

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        for (int i = 0; i < 16; i++) loc_expdata->phenomeKeyFrame.SetValue(i,0.0f);
    }

    bool ExpressionManager::RegisterGagType(RE::BGSKeyword* a_keyword, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        //validate
        if (a_keyword == nullptr || (a_factions.size() != 16 && a_factions.size() != 1) || a_defaults.size() != 16)
        {
            //LOG("ExpressionManager::RegisterGagType - Could not register gag")
            return false;
        }

        //check if the same gag type is not already present!
        const auto loc_foundit = std::find_if(_GagTypes.begin(),_GagTypes.end(),[a_keyword](const GagType& a_type)
        {
            if (a_type.keyword == a_keyword) return true;
            return false;
        });
        if (loc_foundit != _GagTypes.end()) return false;

        _GagTypes.push_back({a_keyword,a_factions,a_defaults});
        return true;
    }

    bool ExpressionManager::RegisterDefaultGagType(std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        //validate
        if ((a_factions.size() != 16 && a_factions.size() != 1) || a_defaults.size() != 16)
        {
            //LOG("ExpressionManager::RegisterDefaultGagType - Could not register gag")
            return false;
        }

        _DefaultGagType = {nullptr,a_factions,a_defaults};

        return true;
    }

    std::vector<float> ExpressionManager::ApplyStrengthToExpression(const std::vector<float>& a_expression, float a_strength)
    {
        if (a_expression.size() != 32) return a_expression;

        std::vector<float> loc_res = a_expression;

        const float loc_mult  = std::clamp(a_strength,0.0f,1.0f);

        for (int i = 0; i < 30; i++)
        {
            loc_res[i] *= loc_mult;
        }

        loc_res[31] *= loc_mult;

        return loc_res;
    }

    int ExpressionManager::UpdateGagExpForNPCs()
    {
        RE::PlayerCharacter* loc_player = RE::PlayerCharacter::GetSingleton(); 

        if (loc_player == nullptr) return 0;

        uint16_t loc_updated = 0;

        if (IsGagged(loc_player))
        {
            loc_updated += 1;
            UpdateGagExpression(loc_player);
        }

        if (!ConfigManager::GetSingleton()->GetVariable<int>("GagExpression.bNPCsEnabled", true)) {
            return loc_updated;
        }

        const int loc_distance = ConfigManager::GetSingleton()->GetVariable<int>("GagExpression.iNPCDistance", 500);

        LOG("UpdateGagExpForNPCs() called - Distance = {}", loc_distance)

        Utils::ForEachActorInRange(loc_distance, [&](RE::Actor* a_actor) {
            auto loc_refBase = a_actor->GetActorBase();

            if (a_actor && !a_actor->IsDisabled() && a_actor->Is3DLoaded() && !a_actor->IsPlayerRef() &&
                IsGagged(a_actor) &&
                (a_actor->Is(RE::FormType::NPC) || (loc_refBase && loc_refBase->Is(RE::FormType::NPC))))
            {
                loc_updated += 1;
                UpdateGagExpression(a_actor);
            }
        });

        return loc_updated;
    }

    std::vector<float> ExpressionManager::GetGagEffectPreset(RE::Actor* a_actor)
    {
        std::vector<float> loc_res(16,0);

        const RE::TESObjectARMO* loc_gag = LibFunctions::GetSingleton()->GetWornArmor(a_actor,(int)RE::BIPED_MODEL::BipedObjectSlot::kModMouth);

        if (loc_gag == nullptr) return loc_res;

        bool loc_gagtypefound = false;
        for (auto&& it : _GagTypes)
        {
            if (loc_gag->HasKeyword(it.keyword))
            {
                ApplyPhonemsFaction(a_actor,loc_res,it.factions,it.defaults);
                loc_gagtypefound = true;
                break;
            }
        }

        //check if gag type was found. If not, use default one
        if (!loc_gagtypefound) 
        {
            //WARN("No gag type found! Using default type")
            ApplyPhonemsFaction(a_actor,loc_res,_DefaultGagType.factions,_DefaultGagType.defaults);
        }

        return loc_res;
    }
}