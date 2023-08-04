#include "Expression.h"

namespace DeviousDevices
{
    std::vector<float> ApplyExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<float> a_expression, int a_control)
    {
        return _ApplyExpression(a_actor, a_expression, a_control);
    }

    std::vector<float> GetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor)
    {   
        return _GetExpression(a_actor);
    }

    void ResetExpression(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, bool a_phonem, bool b_mods)
    {
        _ResetExpression(a_actor,a_phonem,b_mods);
    }

    std::vector<float> FactionsToPreset(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
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

    std::vector<float> ApplyPhonemsFaction(PAPYRUSFUNCHANDLE, RE::Actor* a_actor, std::vector<float> a_exp, std::vector<RE::TESFaction*> a_factions, std::vector<int> a_defaults)
    {
        if (a_actor == nullptr) return a_exp;

        if (a_factions.size() > 0)
        {
            for(int i =0; i < a_factions.size();i++)
            {
                int loc_rank = std::clamp(a_actor->GetFactionRank(a_factions[i],a_actor->IsPlayer()),-1,100);
                if (loc_rank >= 0)  (a_exp[i] = loc_rank/100.0f);
                else                (a_exp[i] = a_defaults[i]/100.0f);
            }
        }
        else
        {
            for(int i =0; i < a_defaults.size();i++)
            {
                a_exp[i] = std::clamp(a_defaults[i],0,100)/100.0f;
            }
        }
        return a_exp;
    }

    std::vector<float> _ApplyExpression(RE::Actor* a_actor, const std::vector<float> &a_expression, int a_control)
    {
        if (a_actor == nullptr) return std::vector<float>();

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return std::vector<float>();

        if (a_expression.size() == 0U) return _GetExpression(a_actor);

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        bool loc_phonems    = a_control & 0x1;
        bool loc_mods       = a_control & 0x2;

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
        return _GetExpression(a_actor);
    }

    std::vector<float> _GetExpression(RE::Actor* a_actor)
    {
        if (a_actor == nullptr) return std::vector<float>(32,0.0f);

        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();
        
        if (loc_expdata == nullptr) return std::vector<float>(32,0.0f);

        std::vector<float> loc_res;

        for (int i = 0; i < 16; i++) loc_res.push_back(loc_expdata->phenomeKeyFrame.values[i]); 
        for (int i = 0; i < 14; i++) loc_res.push_back(loc_expdata->modifierKeyFrame.values[i]);

        return loc_res;
    }

    void _ResetExpression(RE::Actor* a_actor, bool a_phonem, bool a_mods)
    {
        if (a_actor == nullptr) return;
        
        RE::BSFaceGenAnimationData* loc_expdata = a_actor->GetFaceGenAnimationData();

        if (loc_expdata == nullptr) return;

        RE::BSSpinLockGuard locker(loc_expdata->lock);

        if (a_phonem) 
        {
            for (int i = 0; i < 16; i++) loc_expdata->phenomeKeyFrame.SetValue(i,0.0f);
        }
        if (a_mods)
        {
            for (int i = 0; i < 14; i++)   loc_expdata->modifierKeyFrame.SetValue(i,0.0f);
        }
    }
}