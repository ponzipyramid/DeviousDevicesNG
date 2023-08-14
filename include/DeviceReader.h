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
        std::unique_ptr<uint8_t> data;
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
        uint32_t GetProperty(std::string a_name);
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

        std::string name;
        DeviceGroup group_TES4;
        DeviceGroup group_ARMO;
        size_t      size;
        uint8_t*    rawdata = nullptr;
        std::vector<std::unique_ptr<DeviceHandle>> devicerecords;
        std::vector<std::string>   masters;
    };

    class DeviceReader
    {
    SINGLETONHEADER(DeviceReader)
    public:
        void Setup();

        RE::TESObjectARMO* GetDeviceRender(RE::TESObjectARMO* a_invdevice); 
    private:
        void LoadDDMods();

        void ParseMods();

        std::vector<RE::TESFile*>                       _ddmods;
        std::vector<std::unique_ptr<DeviceMod>>         _ddmodspars;
        std::map<RE::TESObjectARMO*,RE::TESObjectARMO*> _database;
        void LoadDB();
    };
}