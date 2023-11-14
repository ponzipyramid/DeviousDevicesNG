#include "Papyrus.h"
#include "Expression.h"
#include "Hider.h"
#include "NodeHider.h"
#include "DeviceReader.h"
#include "LibFunctions.h"
#include <functional>
#include <algorithm>

using namespace RE;
using namespace RE::BSScript;
using namespace REL;
using namespace SKSE;
namespace DeviousDevices {
    constexpr std::string_view PapyrusClass = "zadNativeFunctions";

    bool FormHasKeywordString(StaticFunctionTag* base, TESForm* obj, std::string kwd) {
        if (!obj) {
            LOG("FormHasKeywordString received none obj.");
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
        LOG("Received string: {}", msg);
        return false;
    }

    TESForm* FindMatchingDevice(StaticFunctionTag* base, Actor* obj, BGSKeyword* kwd) {
        if (!obj) {
            LOG("ReEquipExistingDevice received NULL obj.");
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

    void CTrace(PAPYRUSFUNCHANDLE, std::string a_msg)
    {
        if (RE::ConsoleLog::GetSingleton() != nullptr)
        {
            RE::ConsoleLog::GetSingleton()->Print((std::string("[DD] ") + a_msg).c_str());
        }
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
    REGISTERPAPYRUSFUNC(FormHasKeywordString,true);
    REGISTERPAPYRUSFUNC(FindMatchingDevice,true);
    REGISTERPAPYRUSFUNC(CTrace,true);

    //Expression.h
    REGISTERPAPYRUSFUNC(ApplyExpression,true);
    REGISTERPAPYRUSFUNC(GetExpression,true);
    REGISTERPAPYRUSFUNC(ResetExpression,true);
    REGISTERPAPYRUSFUNC(UpdateGagExpression,true);
    REGISTERPAPYRUSFUNC(RegisterGagType,true);
    REGISTERPAPYRUSFUNC(RegisterDefaultGagType,true);
    REGISTERPAPYRUSFUNC(ResetGagExpression,true);

    //hider
    REGISTERPAPYRUSFUNC(SyncSetting,true);
    REGISTERPAPYRUSFUNC(SetActorStripped,true);
    REGISTERPAPYRUSFUNC(IsActorStripped,true);

    //node hider
    REGISTERPAPYRUSFUNC(HideWeapons,true);
    REGISTERPAPYRUSFUNC(ShowWeapons,true);

    //device reader
    REGISTERPAPYRUSFUNC(GetRenderDevice,true);
    REGISTERPAPYRUSFUNC(GetInventoryDevice,true);
    REGISTERPAPYRUSFUNC(GetPropertyForm,true);
    REGISTERPAPYRUSFUNC(GetPropertyInt,true);
    REGISTERPAPYRUSFUNC(GetPropertyFloat,true);
    REGISTERPAPYRUSFUNC(GetPropertyBool,true);
    REGISTERPAPYRUSFUNC(GetPropertyString,true);
    REGISTERPAPYRUSFUNC(GetPropertyFormArray,true);
    REGISTERPAPYRUSFUNC(GetPropertyIntArray,true);
    REGISTERPAPYRUSFUNC(GetPropertyFloatArray,true);
    REGISTERPAPYRUSFUNC(GetPropertyBoolArray,true);
    REGISTERPAPYRUSFUNC(GetPropertyStringArray,true);
    REGISTERPAPYRUSFUNC(GetEditingMods,true);
    REGISTERPAPYRUSFUNC(GetDeviceByName,true);

    REGISTERPAPYRUSFUNC(SetManipulated, true);
    REGISTERPAPYRUSFUNC(GetManipulated, true);

    //LibFunctions
    REGISTERPAPYRUSFUNC(GetDevices, true);
    REGISTERPAPYRUSFUNC(GetWornDevice, true);

    #undef REGISTERPAPYRUSFUNC
    return true;
}