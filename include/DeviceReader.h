#pragma once

namespace DeviousDevices
{
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

    struct DeviceHandle
    {
        DeviceRecord                    record;
        std::string                     source;
        ScriptHandle                    scripts;
        KeywordsHandle                  keywords;
        
        void LoadVM();
        void LoadKeywords();

        //only usable form form properties
        //will rework this in future so it will be possible to read all types of properties from file
        std::pair<std::shared_ptr<uint8_t>,uint8_t> GetPropertyRaw(std::string a_name);  //get raw property <data,type>

        uint32_t    GetPropertyOBJ(std::string a_name,bool a_silence);  //get object (internal form id)
        int32_t     GetPropertyINT(std::string a_name);  //get int
        float       GetPropertyFLT(std::string a_name);  //get float
        bool        GetPropertyBOL(std::string a_name);  //get bool
        std::string GetPropertySTR(std::string a_name);  //get string

        std::vector<uint32_t>       GetPropertyOBJA(std::string a_name);  //get object (internal form id) array
        std::vector<int32_t>        GetPropertyINTA(std::string a_name);  //get int array
        std::vector<float>          GetPropertyFLTA(std::string a_name);  //get float array
        std::vector<bool>           GetPropertyBOLA(std::string a_name);  //get bool array
        std::vector<std::string>    GetPropertySTRA(std::string a_name);  //get string array
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

        void ParseInfo();
        size_t ParseDevices();

        RE::TESForm* GetForm(const DeviceHandle* a_handle);
        RE::TESForm* GetForm(const uint32_t a_formID); //have to be internal esp formID !!!

        template <typename T>
        T* GetForm(const uint32_t a_formID);  // have to be internal esp formID !!!

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
            bool CanEquip(RE::Actor* actor);
            inline RE::TESObjectARMO* GetRenderedDevice() { return deviceRendered; }
            inline RE::BGSMessage* GetEquipMenu() { return equipMenu; }
            inline RE::BGSMessage* GetManipulationMenu() { return zad_DD_OnPutOnDevice; }
            inline std::string GetName() { return deviceInventory->GetFormEditorID(); }
            inline RE::FormID GetFormID() { return deviceInventory->GetFormID(); }

            RE::BGSKeyword* kwd;

            RE::BGSMessage* equipMenu;
            RE::BGSMessage* zad_DD_OnPutOnDevice;
            RE::BGSMessage* zad_EquipRequiredFailMsg;
            RE::BGSMessage* zad_EquipConflictFailMsg;

            std::vector<RE::BGSKeyword*> equipConflictingDeviceKwds;
            std::vector<RE::BGSKeyword*> requiredDeviceKwds;
            std::vector<RE::BGSKeyword*> unequipConflictingDeviceKwds;
          
            bool lockable;
            bool canManipulate;

            RE::TESObjectARMO*              deviceInventory;
            RE::TESObjectARMO*              deviceRendered;

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
        DeviceUnit GetDeviceUnit(RE::TESObjectARMO* a_invdevice);


        inline bool IsInventoryDevice(RE::TESForm* obj) {
            return obj->HasKeywordInArray(invDeviceKwds, true);
        }

        inline DeviceUnit* GetInventoryDevice(RE::TESForm* obj) { return devices.count(obj->GetFormID()) ? devices[obj->GetFormID()] : nullptr; }

        bool CanEquipDevice(RE::Actor* actor, DeviceUnit* obj);

        bool EquipRenderedDevice(RE::Actor* actor, DeviceUnit* device);

        void ShowEquipMenu(DeviceUnit* device, std::function<void(bool)> callback);

        void ShowManipulateMenu(RE::Actor* actor, DeviceUnit* device);

        void ShowEquipConfirmation(DeviceUnit* device);

        DeviceUnit GetDeviceUnit(std::string a_name);

        template <typename T>
        T* GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname,
                                             int a_mode);  // NOT TESTED
        RE::TESForm*    GetPropertyForm(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);


        int             GetPropertyInt(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                       
        float           GetPropertyFloat(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                     
        bool            GetPropertyBool(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                      //NOT TESTED
        std::string     GetPropertyString(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                    
        std::vector<int>            GetPropertyIntArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);      //NOT TESTED
        std::vector<float>          GetPropertyFloatArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);    //NOT TESTED
        std::vector<bool>           GetPropertyBoolArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);     //NOT TESTED
        std::vector<std::string>    GetPropertyStringArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);   

        template <typename T>
        std::vector<T*> GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname,
                                                       int a_mode);  // NOT TESTED
        std::vector<RE::TESForm*> GetPropertyFormArray(RE::TESObjectARMO* a_invdevice, std::string a_propertyname,
                                                       int a_mode);  // NOT TESTED

        inline void SetManipulated(RE::Actor* actor, RE::TESObjectARMO* inv, bool manip) { 
            auto pair = std::pair<RE::FormID, RE::FormID>(actor->GetFormID(), inv->GetFormID());
            if (manip)
                manipulated.insert(pair);
            else
                manipulated.erase(pair);
        
        }

        inline bool GetManipulated(RE::Actor* actor, RE::TESObjectARMO* inv) {
            return manipulated.contains(std::pair<RE::FormID, RE::FormID>(actor->GetFormID(), inv->GetFormID())); 
        }

        

        inline bool ShouldEquipSilently(RE::Actor* akActor) {
            if (zad_AlwaysSilent->HasForm(akActor)) {
                return true;
            }

            auto ui = RE::UI::GetSingleton();
            auto invMenu = ui->GetMenu(RE::InventoryMenu::MENU_NAME);
            auto containerMenu = ui->GetMenu(RE::ContainerMenu::MENU_NAME);

            return !containerMenu.get() && !(akActor->GetFormID() == 20 && invMenu.get());
        }

    private:
        void LoadDDMods();
        void ParseMods();
        void LoadDB();

        RE::BGSListForm* zad_AlwaysSilent;
        
        std::vector<RE::TESFile*>                       _ddmods;
        std::vector<std::shared_ptr<DeviceMod>>         _ddmodspars;
        std::map<RE::TESObjectARMO*, DeviceUnit>         _database;

        std::unordered_map<RE::FormID, DeviceUnit*> devices;
        std::vector<RE::BGSKeyword*> invDeviceKwds;

        std::set<std::pair<RE::FormID, RE::FormID>> manipulated; // serde
    };


    //=== Papyrus native functions
    RE::TESObjectARMO* GetRenderDevice(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice);
    RE::TESObjectARMO* GetDeviceByName(PAPYRUSFUNCHANDLE,std::string a_name); //just because this exist doesn't mean that it should be used ;)

    //read interface
    RE::TESForm*    GetPropertyForm(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                      
    int             GetPropertyInt(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                       
    float           GetPropertyFloat(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                     
    bool            GetPropertyBool(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                      //NOT TESTED
    std::string     GetPropertyString(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);                    
    std::vector<RE::TESForm*>   GetPropertyFormArray(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);     //NOT TESTED
    std::vector<int>            GetPropertyIntArray(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);      //NOT TESTED
    std::vector<float>          GetPropertyFloatArray(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);    //NOT TESTED
    std::vector<bool>           GetPropertyBoolArray(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);     //NOT TESTED
    std::vector<std::string>    GetPropertyStringArray(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode);   


    // device manipulation
    inline void SetManipulated(PAPYRUSFUNCHANDLE, RE::Actor* actor, RE::TESObjectARMO* inv, bool manip) {
        DeviceReader::GetSingleton()->SetManipulated(actor, inv, manip);
    }
    inline bool GetManipulated(PAPYRUSFUNCHANDLE, RE::Actor* actor, RE::TESObjectARMO* inv) {
        return DeviceReader::GetSingleton()->GetManipulated(actor, inv);
    }

    //returns all mods which edited the device
    std::vector<std::string>    GetEditingMods(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice);
}