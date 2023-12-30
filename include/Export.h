#pragma once
#include "DeviceReader.h"

//Device mod prototype
struct DeviceModPrototype
{
    std::string name;
    uint8_t group_TES4[32];
    uint8_t group_ARMO[32];
    size_t      size;
    uint8_t*    rawdata = nullptr;
    std::vector<uint8_t[16]> devicerecords;
    std::vector<std::string>   masters;
};
static_assert(sizeof(DeviceModPrototype) == sizeof(DeviousDevices::DeviceMod));


//Device unit prototype
struct DeviceUnitPrototype
{
    std::string scriptName;

    RE::BGSKeyword* kwd                         = nullptr;

    RE::BGSMessage* equipMenu                   = nullptr;
    RE::BGSMessage* zad_DD_OnPutOnDevice        = nullptr;
    RE::BGSMessage* zad_EquipRequiredFailMsg    = nullptr;
    RE::BGSMessage* zad_EquipConflictFailMsg    = nullptr;

    std::vector<RE::BGSKeyword*> equipConflictingDeviceKwds;
    std::vector<RE::BGSKeyword*> requiredDeviceKwds;
    std::vector<RE::BGSKeyword*> unequipConflictingDeviceKwds;
          
    bool lockable;
    bool canManipulate;

    RE::TESObjectARMO*              deviceInventory = nullptr;
    RE::TESObjectARMO*              deviceRendered  = nullptr;

    //following values are set to last values found on last mod (so last overriding mod)
    uint8_t                                 padd_A[16]; //device handle with raw data
    std::vector<RE::BGSKeyword*>            keywords;   //array of keywords loaded from esp - uses keywords from last loaded mod
    std::shared_ptr<DeviceModPrototype>     deviceMod;  //device source mod
            
    //stack of changes by mods. Last record => previous 3 values. First record => original mod record before changes from other mods
    struct HistoryRecord
    {
        std::shared_ptr<DeviceModPrototype> deviceMod;
        uint8_t padd_CB[16];
        std::vector<RE::BGSKeyword*>    keywords;
    };
    std::vector<HistoryRecord>      history; //history stack
};
static_assert(sizeof(DeviceUnitPrototype) == sizeof(DeviousDevices::DeviceReader::DeviceUnit));

extern "C"
{
    DLLEXPORT const std::map<RE::TESObjectARMO*, DeviceUnitPrototype>& GetDatabase()
    {
        return *(const std::map<RE::TESObjectARMO*, DeviceUnitPrototype>*)&DeviousDevices::DeviceReader::GetSingleton()->GetDatabase();
    }

    DLLEXPORT RE::TESObjectARMO* GetDeviceRender(RE::TESObjectARMO* a_invdevice)
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetDeviceRender(a_invdevice);
    } 

    DLLEXPORT RE::TESObjectARMO* GetDeviceInventory(RE::TESObjectARMO* a_renddevice)
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetDeviceInventory(a_renddevice);
    } 

    DLLEXPORT RE::TESForm* GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, RE::TESForm* a_defvalue, int a_mode) 
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyForm(a_invdevice,a_propertyname,a_defvalue,a_mode);
    }

    DLLEXPORT int GetPropertyInt(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_defvalue, int a_mode)
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyInt(a_invdevice,a_propertyname,a_defvalue,a_mode);
    }

    DLLEXPORT float GetPropertyFloat(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, float a_defvalue, int a_mode)
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFloat(a_invdevice,a_propertyname,a_defvalue,a_mode);
    }

    DLLEXPORT bool GetPropertyBool(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, bool a_defvalue, int a_mode)
    {
        return DeviousDevices::DeviceReader::GetSingleton()->GetPropertyBool(a_invdevice,a_propertyname,a_defvalue,a_mode);
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::string* GetPropertyString(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, std::string a_defvalue, int a_mode)
    {
        return new std::string(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyString(a_invdevice,a_propertyname,a_defvalue,a_mode));
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::vector<RE::TESForm*>* GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
    {
        return new std::vector<RE::TESForm*>(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFormArray(a_invdevice,a_propertyname,a_mode));
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::vector<int>* GetPropertyIntArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
    {
        return new std::vector<int>(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyIntArray(a_invdevice,a_propertyname,a_mode));
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::vector<float>* GetPropertyFloatArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
    {
        return new std::vector<float>(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyFloatArray(a_invdevice,a_propertyname,a_mode));
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::vector<bool>* GetPropertyBoolArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
    {
        return new std::vector<bool>(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyBoolArray(a_invdevice,a_propertyname,a_mode));
    }

    //do not forget to free up memory after using result!!!
    DLLEXPORT std::vector<std::string>* GetPropertyStringArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
    {
        return new std::vector<std::string>(DeviousDevices::DeviceReader::GetSingleton()->GetPropertyStringArray(a_invdevice,a_propertyname,a_mode));
    }
}