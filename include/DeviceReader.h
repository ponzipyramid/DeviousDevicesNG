#pragma once

#include "ConflictMap.h"

namespace DeviousDevices
{
    struct FormHandle
    {
        RE::FormID  id;
        std::string mod;
    };

    struct Property
    {
        enum class PropertyTypes
        {
            kObject         = 1,
            kWString        = 2,
            kInt            = 3,
            kFloat          = 4,
            kBool           = 5,
            // 6 - 10 = unused
            kArrayObject    = 11,
            kArrayWString   = 12,
            kArrayInt       = 13,
            kArrayFloat     = 14,
            kArrayBool      = 15
        };

        std::string propertyName;
        uint8_t propertyType;
        uint8_t status;
        std::shared_ptr<uint8_t> data;
    };

    struct Script
    {
        std::string scriptName;
        uint8_t status;
        uint16_t propertyCount;
        std::vector<std::unique_ptr<Property>> properties;
    };

    struct ScriptHandle
    {
        int16_t version;
        int16_t objFormat;
        uint16_t scriptCount;
        std::vector<std::unique_ptr<Script>> scripts; 
    };

    struct FieldHeader
    {
        uint8_t     type[4];        //00
        uint16_t    size;           //04
    };

    struct KeywordsHandle
    {
        //field KSIZ
        struct KSIZ
        {
            FieldHeader header;
            uint32_t    keywordcount;
        } ksiz;
        
        //field KWDA
        struct KWDA
        {
            FieldHeader               header;
            std::shared_ptr<uint32_t> data; 
        } kwda;
    };

    struct DeviceRecord
    {
        ~DeviceRecord(){ delete[] data; }
        uint8_t     type[4];        //00
        uint32_t    size;           //04
        uint32_t    flags;          //08
        uint32_t    formId;         //12
        uint16_t    timestamp;      //14
        uint16_t    version;        //16
        uint16_t    version_i;      //18
        uint16_t    unkw_1;         //20
        uint8_t*    data = nullptr; //24 - size
    };

    class DeviceMod;

    struct DeviceHandle
    {
        DeviceRecord                    record;
        std::string                     source;
        ScriptHandle                    scripts;
        KeywordsHandle                  keywords;
        DeviceMod*                      mod;
        
        void LoadVM();
        void LoadKeywords();

        //only usable form form properties
        //will rework this in future so it will be possible to read all types of properties from file
        std::pair<std::shared_ptr<uint8_t>,uint8_t> GetPropertyRaw(std::string a_name) const;  //get raw property <data,type>

        uint32_t    GetPropertyOBJ(std::string a_name, uint32_t     a_defvalue, bool a_silence) const;  //get object (internal form id)
        int32_t     GetPropertyINT(std::string a_name, int32_t      a_defvalue) const;  //get int
        float       GetPropertyFLT(std::string a_name, float        a_defvalue) const;  //get float
        bool        GetPropertyBOL(std::string a_name, bool         a_defvalue) const;  //get bool
        std::string GetPropertySTR(std::string a_name, std::string  a_defvalue) const;  //get string

        std::vector<uint32_t>       GetPropertyOBJA(std::string a_name) const;  //get object (internal form id) array
        std::vector<int32_t>        GetPropertyINTA(std::string a_name) const;  //get int array
        std::vector<float>          GetPropertyFLTA(std::string a_name) const;  //get float array
        std::vector<bool>           GetPropertyBOLA(std::string a_name) const;  //get bool array
        std::vector<std::string>    GetPropertySTRA(std::string a_name) const;  //get string array

        template<typename T>
        T* GetFormFromHandle(const RE::FormID &a_formid) const;
    };

    struct DeviceGroup
    {
        ~DeviceGroup(){ delete[] data; }
        uint8_t     grup[4];        //00
        uint32_t    size = 0U;      //04
        uint8_t     label[4];       //08
        int32_t     type;           //12
        uint16_t    timestamp;      //14
        uint16_t    version;        //16
        uint32_t    uknw_1;         //20
        uint8_t*    data = nullptr; //24 - size
    };

    struct DeviceMod
    {
        DeviceMod(std::string a_name, uint8_t* a_data, size_t a_size);
        ~DeviceMod(){ delete rawdata; }

        void    ParseInfo();
        size_t  ParseDevices();

        RE::TESForm* GetForm(const DeviceHandle* a_handle) const;
        template <typename T>
        T* GetForm(const uint32_t a_formID) const;  // have to be internal esp formID !!!

        std::string name;
        DeviceGroup group_TES4;
        DeviceGroup group_ARMO;
        size_t      size;
        uint8_t*    rawdata = nullptr;
        std::vector<std::shared_ptr<DeviceHandle>> devicerecords;
        std::vector<std::string>   masters;
    };

    class DeviceReader
    {
    SINGLETONHEADER(DeviceReader)
    public:
        struct DeviceUnit
        {
            bool                        CanEquip(RE::Actor* actor) const;
            inline RE::TESObjectARMO*   GetRenderedDevice() const { return deviceRendered; }
            inline RE::BGSMessage*      GetEquipMenu() const { return equipMenu; }
            inline RE::BGSMessage*      GetManipulationMenu() const { return zad_DD_OnPutOnDevice; }
            inline std::string          GetName() const { return deviceInventory->GetName(); }
            inline RE::FormID           GetFormID() const { return deviceInventory->GetFormID(); }

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
            std::shared_ptr<DeviceHandle>   deviceHandle;               //device handle with raw data
            std::vector<RE::BGSKeyword*>    keywords;                   //array of keywords loaded from esp - uses keywords from last loaded mod
            std::shared_ptr<DeviceMod>      deviceMod;                  //device source mod
            
            //stack of changes by mods. Last record => previous 3 values. First record => original mod record before changes from other mods
            struct HistoryRecord
            {
                std::shared_ptr<DeviceMod>      deviceMod;
                std::shared_ptr<DeviceHandle>   deviceHandle;
                std::vector<RE::BGSKeyword*>    keywords;
            };
            std::vector<HistoryRecord>      history; //history stack
        };

        void Setup();

        RE::TESObjectARMO* GetDeviceRender(RE::TESObjectARMO* a_invdevice); 
        RE::TESObjectARMO* GetDeviceInventory(RE::TESObjectARMO* a_renddevice); 
        DeviceUnit GetDeviceUnit(RE::TESObjectARMO* a_device, int a_mode = 0);


        inline bool IsInventoryDevice(RE::TESForm* obj) const {
            return obj->HasKeywordInArray(_invDeviceKwds, true);
        }

        inline DeviceUnit* GetDevice(RE::TESForm* obj) { return _devices.count(obj->GetFormID()) ? _devices[obj->GetFormID()] : nullptr; }

        bool CanEquipDevice(RE::Actor* actor, DeviceUnit* obj);

        bool EquipRenderedDevice(RE::Actor* actor, DeviceUnit* device);
        bool UnequipRenderedDevice(RE::Actor* actor, DeviceUnit* device);

        void ShowEquipMenu(DeviceUnit* device, std::function<void(bool)> callback);

        void ShowManipulateMenu(RE::Actor* actor, DeviceUnit* device);

        DeviceUnit GetDeviceUnit(std::string a_name);

        template <typename T>
        T*              GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname,uint32_t a_defvalue,int a_mode)  const;
        RE::TESForm*    GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, RE::TESForm* a_defvalue, int a_mode) const;
        int             GetPropertyInt(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_defvalue, int a_mode)      const;
        float           GetPropertyFloat(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, float a_defvalue, int a_mode)  const;
        bool            GetPropertyBool(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, bool a_defvalue, int a_mode)    const;
        std::string     GetPropertyString(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, std::string a_defvalue, int a_mode) const;
        std::vector<int>            GetPropertyIntArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)     const;
        std::vector<float>          GetPropertyFloatArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)   const;
        std::vector<bool>           GetPropertyBoolArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)    const;
        std::vector<std::string>    GetPropertyStringArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)  const;

        template <typename T>
        std::vector<T*> GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const;
        std::vector<RE::TESForm*> GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode) const;

        inline void SetManipulated(RE::Actor* a_actor, RE::TESObjectARMO* a_inv, bool manip) 
        {
            // TODO: Persist this data in co-save
            if ((a_actor == nullptr) || (a_inv == nullptr)) return;
            auto pair = std::pair<RE::FormID, RE::FormID>(a_actor->GetFormID(), a_inv->GetFormID());
            if (manip)  _manipulated.insert(pair);
            else        _manipulated.erase(pair);
        }

        inline bool GetManipulated(RE::Actor* a_actor, RE::TESObjectARMO* a_inv) const
        {
            if ((a_actor == nullptr) || (a_inv == nullptr)) return false;
            return _manipulated.contains(std::pair<RE::FormID, RE::FormID>(a_actor->GetFormID(), a_inv->GetFormID())); 
        }

        inline bool ShouldEquipSilently(RE::Actor* a_actor) const
        {
            if (a_actor == nullptr) return false;

            if (_alwaysSilent->HasForm(a_actor)) {
                return true;
            }

            auto ui = RE::UI::GetSingleton();
            auto invMenu = ui->GetMenu(RE::InventoryMenu::MENU_NAME);
            auto containerMenu = ui->GetMenu(RE::ContainerMenu::MENU_NAME);

            return !containerMenu.get() && !(a_actor->GetFormID() == 20 && invMenu.get());
        }

        DeviceUnit EmptyDeviceUnit;
    private:
        void LoadDDMods();
        void ParseMods();
        void LoadDB();

        RE::BGSListForm*                                        _alwaysSilent;
        std::vector<RE::TESFile*>                               _ddmods;
        std::vector<std::shared_ptr<DeviceMod>>                 _ddmodspars;
        std::map<RE::TESObjectARMO*, DeviceUnit>                _database;
        std::unordered_map<std::string, std::vector<Conflict>>  _deviceConflicts;
        std::unordered_map<RE::FormID, DeviceUnit*>             _devices;
        std::vector<RE::BGSKeyword*>                            _invDeviceKwds;
        std::set<std::pair<RE::FormID, RE::FormID>>             _manipulated; // serde
        bool                                                    _installed = false;
    };


    //=== Papyrus native functions
    RE::TESObjectARMO* GetRenderDevice(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice);
    RE::TESObjectARMO* GetInventoryDevice(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_renddevice);
    RE::TESObjectARMO* GetDeviceByName(PAPYRUSFUNCHANDLE,std::string a_name); //just because this exist doesn't mean that it should be used ;)

    //read interface
    RE::TESForm*    GetPropertyForm(    PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname,RE::TESForm*   a_defvalue, int a_mode);
    int             GetPropertyInt(     PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname,int            a_defvalue, int a_mode);
    float           GetPropertyFloat(   PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname,float          a_defvalue, int a_mode);
    bool            GetPropertyBool(    PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname,bool           a_defvalue, int a_mode);
    std::string     GetPropertyString(  PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname,std::string    a_defvalue, int a_mode);
    std::vector<RE::TESForm*>   GetPropertyFormArray(   PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);
    std::vector<int>            GetPropertyIntArray(    PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);
    std::vector<float>          GetPropertyFloatArray(  PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);
    std::vector<bool>           GetPropertyBoolArray(   PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);
    std::vector<std::string>    GetPropertyStringArray( PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);


    // device manipulation
    inline void SetManipulated(PAPYRUSFUNCHANDLE, RE::Actor* actor, RE::TESObjectARMO* inv, bool manip) 
    {
        LOG("SetManipulated called")
        DeviceReader::GetSingleton()->SetManipulated(actor, inv, manip);
    }
    inline bool GetManipulated(PAPYRUSFUNCHANDLE, RE::Actor* actor, RE::TESObjectARMO* inv) 
    {
        LOG("GetManipulated called")
        return DeviceReader::GetSingleton()->GetManipulated(actor, inv);
    }

    //returns all mods which edited the device
    std::vector<std::string>    GetEditingMods(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice);
}