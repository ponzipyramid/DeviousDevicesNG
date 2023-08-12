#include "Papyrus.h"
#include "Expression.h"
#include "Hider.h"
#include "NodeHider.h"
#include <functional>
#include <algorithm>

using namespace RE;
using namespace RE::BSScript;
using namespace REL;
using namespace SKSE;
namespace DeviousDevices {
    constexpr std::string_view PapyrusClass = "zadNativeFunctions";

    std::string GetName(StaticFunctionTag* base, RE::TESForm* thisForm) {
        if (!thisForm) return "";
        return thisForm->GetName();
    }

    bool FormHasKeywordString(StaticFunctionTag* base, TESForm* obj, std::string kwd) {
        if (!obj) {
            SKSE::log::info("FormHasKeywordString received none obj.");
            return false;
        }
               
        BGSKeyword* keyword = TESForm::LookupByEditorID<BGSKeyword>(kwd);

        if (keyword) {
            std::vector<BGSKeyword*> kwdArr;
            kwdArr.push_back(keyword);
            return obj->HasKeywordInArray(kwdArr, true);
        } 

        return false;
    }

    bool FormHasKeyword(StaticFunctionTag* base, TESForm* obj, BGSKeyword* kwd) {
        if (obj && kwd) {
            std::vector<BGSKeyword*> kwdArr;
            kwdArr.push_back(kwd);
            return obj->HasKeywordInArray(kwdArr, true);
        }
        return false;
    }

    bool Print(StaticFunctionTag* base, std::string msg) {
        SKSE::log::info("Received string: {}", msg);
        return false;
    }

    TESForm* FindMatchingDevice(StaticFunctionTag* base, Actor* obj, BGSKeyword* kwd) {
        if (!obj) {
            SKSE::log::info("ReEquipExistingDevice received NULL obj.");
            return NULL;
        }
        
        std::map < TESBoundObject*, std::int32_t> inventory =
            obj->GetInventoryCounts();
        
        for (auto& entry : inventory) {
            if (FormHasKeyword(base, entry.first, kwd)) {
                return entry.first;
            }
        }

        return NULL;
    }
}

bool DeviousDevices::RegisterFunctions(IVirtualMachine* vm) {
    //unhookfps means that the function will be unhooked from fps which will make it insanily faster. 
    //Note that not all functions can be unhooked from framerate (like some actor setters, as they are dependant on frame update)
    #if (DD_ALLOWFASTPAPYRUSCALL_S == 1U)
        #define REGISTERPAPYRUSFUNC(name,unhookfps) {vm->RegisterFunction(#name, PapyrusClass, DeviousDevices::name,unhookfps);}
    #else
        #define REGISTERPAPYRUSFUNC(name,unhookfps) {vm->RegisterFunction(#name, PapyrusClass, DeviousDevices::name,false);}
    #endif

    //Papyrus.h
    REGISTERPAPYRUSFUNC(GetName,true);
    REGISTERPAPYRUSFUNC(FormHasKeywordString,true);
    REGISTERPAPYRUSFUNC(FindMatchingDevice,true);

    //Expression.h
    REGISTERPAPYRUSFUNC(ApplyExpression,true);
    REGISTERPAPYRUSFUNC(GetExpression,true);
    REGISTERPAPYRUSFUNC(ResetExpression,true);
    REGISTERPAPYRUSFUNC(FactionsToPreset,true);
    REGISTERPAPYRUSFUNC(ApplyPhonemsFaction,true);

    //hider
    REGISTERPAPYRUSFUNC(RebuildSlotMask,true);
    REGISTERPAPYRUSFUNC(FilterMask,true);

    //node hider
    REGISTERPAPYRUSFUNC(HideWeapons,true);
    REGISTERPAPYRUSFUNC(ShowWeapons,true);

    #undef REGISTERPAPYRUSFUNC
    return true;
}