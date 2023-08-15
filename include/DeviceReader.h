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
        void LoadVM();

        //only usable form form properties
        //will rework this in future so it will be possible to read all types of properties from file
        std::pair<std::shared_ptr<uint8_t>,uint8_t> GetPropertyRaw(std::string a_name);  //get raw property <data,type>

        RE::FormID GetPropertyOBJ(std::string a_name, bool a_silence);  // get object (internal form id)
        int32_t  GetPropertyINT(std::string a_name);  //get int
        float    GetPropertyFLT(std::string a_name);  //get float
        bool     GetPropertyBOL(std::string a_name);  //get bool
        std::string GetPropertySTR(std::string a_name);  //get string
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
            inline std::string GetName() { return deviceInventory->GetFormEditorID(); }
            inline RE::FormID GetFormID() { return deviceInventory->GetFormID(); }


            // start new
            
            RE::BGSKeyword* kwd;
            RE::BGSMessage* equipMenu;

            std::vector<RE::BGSKeyword*> equipConflictingDeviceKwds;
            std::vector<RE::BGSKeyword*> requiredDeviceKwds;
            std::vector<RE::BGSKeyword*> unequipConflictingDeviceKwds;

            // end new

            RE::TESObjectARMO*              deviceInventory;
            RE::TESObjectARMO*              deviceRendered;
            std::shared_ptr<DeviceHandle>   deviceHandle;
            std::shared_ptr<DeviceMod>      deviceMod;
        
        };

        void Setup();

        RE::TESObjectARMO* GetDeviceRender(RE::TESObjectARMO* a_invdevice); 
        DeviceUnit GetDeviceUnit(RE::TESObjectARMO* a_invdevice);

        inline bool IsInventoryDevice(RE::TESForm* obj) {
            return obj->HasKeywordInArray(invDeviceKwds, true);
        }

        bool CanEquipDevice(RE::Actor* actor, RE::TESForm* obj);

        bool EquipRenderedDevice(RE::Actor* actor, RE::TESForm* device);

        void ShowEquipMenu(RE::TESForm* device, std::function<void(bool)> callback);


    private:
        void LoadDDMods();
        void ParseMods();
        void LoadDB();
        
        std::vector<RE::TESFile*>                       _ddmods;
        std::vector<std::shared_ptr<DeviceMod>>         _ddmodspars;
        std::map<RE::TESObjectARMO*, DeviceUnit>         _database;
        std::unordered_map<RE::FormID, DeviceUnit*> devices;
        std::vector<RE::BGSKeyword*> invDeviceKwds;
    };


    //=== Papyrus native functions
    RE::TESObjectARMO* GetRenderDevice(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice);

    //read interface
    RE::TESForm*    GetPropertyForm(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname);
    int             GetPropertyInt(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname);
    float           GetPropertyFloat(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname);
    bool            GetPropertyBool(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname);
    std::string     GetPropertyString(PAPYRUSFUNCHANDLE,RE::TESObjectARMO* a_invdevice, std::string a_propertyname);
    //TODO: Arrays (pain)


}