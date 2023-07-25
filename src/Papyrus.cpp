#include "Papyrus.h"
#include "Expression.h"
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
        
        std::map<TESBoundObject*, std::int32_t> inventory = obj->GetInventoryCounts();
        
        for (auto& entry : inventory) {
            if (FormHasKeyword(base, entry.first, kwd)) {
                return entry.first;
            }
        }

        return NULL;
    }
}

bool DeviousDevices::RegisterFunctions(IVirtualMachine* vm) {
    #define REGISTERPAPYRUSFUNC(name) {vm->RegisterFunction(#name, PapyrusClass, DeviousDevices::name);}

    //Papyrus.h
    REGISTERPAPYRUSFUNC(GetName);
    REGISTERPAPYRUSFUNC(FormHasKeywordString);
    REGISTERPAPYRUSFUNC(FindMatchingDevice);

    //expression.h
    REGISTERPAPYRUSFUNC(ApplyExpression);
    REGISTERPAPYRUSFUNC(GetExpression);
    REGISTERPAPYRUSFUNC(ResetExpression);
    REGISTERPAPYRUSFUNC(FactionsToPreset);
    REGISTERPAPYRUSFUNC(ApplyPhonemsFaction);


    #undef REGISTERPAPYRUSFUNC
	return true;
}