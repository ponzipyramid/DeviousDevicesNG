#include <DeviceReader.h>

SINGLETONBODY(DeviousDevices::DeviceReader)

void DeviousDevices::DeviceReader::Setup()
{
    LoadDDMods();
    ParseMods();
    LoadDB();
}

RE::TESObjectARMO* DeviousDevices::DeviceReader::GetDeviceRender(RE::TESObjectARMO* a_invdevice)
{
    return _database[a_invdevice].deviceRendered;
}

void DeviousDevices::DeviceReader::LoadDDMods()
{
    LOG("=== Checking DD mods")

    _ddmods.clear();

    RE::BSSimpleList<RE::TESFile*>* loc_filelist = &RE::TESDataHandler::GetSingleton()->files;
    RE::TESFile* loc_DDA;

    const std::array<std::string,4> loc_masters = {"Devious Devices - Assets.esm","Devious Devices - Integration.esm","Devious Devices - Expansion.esm","Devious Devices - Contraptions.esm"};
    
    for (auto && it : *loc_filelist)
    {
      if ( std::any_of(loc_masters.begin(), loc_masters.end(), 
          [&](std::string a_ddmaster)
          {
            if (it->GetFilename() == a_ddmaster)
            {
                return true;
            }
            else if (std::any_of(it->masters.begin(), it->masters.end(), 
            [&](std::string a_master)
            {
               if (a_master == a_ddmaster) return true;
               else return false;
            }
            ))
            {
                return true;
            }
            else return false;
          }
      ))
      {
        _ddmods.push_back(it);
        
      }
    }
    LOG("=== DD mods found: {:03}",_ddmods.size())
    CLOG("Mods found = {:02}",_ddmods.size())
    for (size_t i = 0; i<_ddmods.size();i++) 
    {
        LOG("{:2} - {}",i,_ddmods[i]->GetFilename())
        CLOG("{:02} - {}",i,_ddmods[i]->GetFilename())
    }
}

void DeviousDevices::DeviceReader::ParseMods()
{
    for (auto && it : _ddmods)
    {
        const std::string loc_path = std::filesystem::current_path().string() + "\\Data\\" + std::string(it->GetFilename());
        LOG("Parsing mod {}, path = {}",it->GetFilename(),loc_path)
        std::fstream loc_file(loc_path,std::ios::binary | std::ios::beg | std::ios::in);
        if (loc_file.is_open())
        {
            size_t loc_size = std::filesystem::file_size(loc_path);
            uint8_t* loc_rawdata = new uint8_t[loc_size];
            loc_file.read(reinterpret_cast<char *>(loc_rawdata),loc_size);
            loc_file.close();
            _ddmodspars.push_back(std::shared_ptr<DeviceMod>(new DeviceMod(std::string(it->GetFilename()),loc_rawdata,loc_size)));
        }
        else LOG("Failed to open file {}",it->GetFilename())
    }
}

DeviousDevices::DeviceReader::DeviceUnit DeviousDevices::DeviceReader::GetDeviceUnit(RE::TESObjectARMO* a_invdevice)
{
    return _database[a_invdevice];
}

DeviousDevices::DeviceReader::DeviceUnit DeviousDevices::DeviceReader::GetDeviceUnit(std::string a_name)
{
    for (auto&& it : _database)
    {
        if (it.first->GetName() == a_name) return it.second;
    }
    return DeviceUnit();
}

void DeviousDevices::DeviceReader::LoadDB()
{
    LOG("=== Building database")
    for (auto && it1 : _ddmodspars)
    {
        //LOG("Checking devices in mod {}",it1->name)
        for (auto && it2 : it1->devicerecords)
        {
            uint32_t loc_formid1 = it2->GetPropertyOBJ("deviceInventory",true);
            uint32_t loc_formid2 = it2->GetPropertyOBJ("deviceRendered",true);
            //LOG("FormID {} , {} found",loc_formid1,loc_formid2)
            if (loc_formid1 > 0 && loc_formid2 > 0)
            {
                RE::TESObjectARMO* loc_ID = reinterpret_cast<RE::TESObjectARMO*>(it1->GetForm(loc_formid1));
                RE::TESObjectARMO* loc_RD = reinterpret_cast<RE::TESObjectARMO*>(it1->GetForm(loc_formid2));
                if (loc_ID && loc_RD) 
                {   
                    const bool loc_original = (_database.find(loc_ID) == _database.end());

                    //LOG("Device {} , {:X} found",loc_ID->GetName(),loc_RD->GetFormID())
                    _database[loc_ID].deviceInventory = loc_ID;
                    _database[loc_ID].deviceRendered  = loc_RD;
                    _database[loc_ID].deviceHandle    = it2;
                    _database[loc_ID].deviceMod       = it1;

                    std::vector<RE::BGSKeyword*> loc_keywords(_database[loc_ID].deviceHandle->keywords.ksiz.keywordcount);
                    for (int i = 0; i < loc_keywords.size(); i++)
                    {
                        const uint32_t loc_formId = _database[loc_ID].deviceHandle->keywords.kwda.data.get()[i];
                        RE::BGSKeyword* loc_kw = reinterpret_cast<RE::BGSKeyword*>(it1->GetForm(loc_formId));
                        loc_keywords[i] = loc_kw;
                    }

                    _database[loc_ID].keywords        = loc_keywords;

                    DeviceReader::DeviceUnit::HistoryRecord loc_changes;
                    loc_changes.deviceHandle    = it2;
                    loc_changes.deviceMod       = it1;
                    loc_changes.keywords        = loc_keywords;

                    _database[loc_ID].history.push_back(loc_changes); //add changes to history stack

                } 
                else LOG("!!!Device not found!!!")
            }
        }
    }

    LOG("=== Building database DONE - Size = {}",_database.size())
    CLOG("Database loaded! Size = {}",_database.size())

    #if (DD_PRINTDB == 1U)
        for (auto&& it : _database) 
        {
            LOG("Database entry: 0x{:08X} = 0x{:08X} ({})",
                    it.second.deviceInventory->GetFormID(),
                    it.second.deviceRendered->GetFormID(),
                    it.second.deviceInventory->GetName() )
            LOG("\tMod stack size = {:2}",it.second.history.size())
            for (size_t i = 0; i < it.second.history.size(); i++) LOG("\t0x{:02X} - {}",i,it.second.history[i].deviceMod->name)
        }
    #endif
}

DeviousDevices::DeviceMod::DeviceMod(std::string a_name, uint8_t* a_data, size_t a_size)
{
    size = a_size;
    rawdata = a_data;
    name = a_name;
    size_t loc_fptr = 0x00000000;

    static const size_t loc_headersize = (sizeof(DeviceGroup) - sizeof(uint8_t*));

    //parse
    while ((loc_fptr + loc_headersize) < size)
    {
        DeviceGroup loc_tmp;

        memcpy(&loc_tmp,&rawdata[loc_fptr],loc_headersize);
        loc_fptr += loc_headersize; //move file pointer

        //soo, it looks like that the uesp wiki was lying. The data size is actually correct size of data without header. 
        //And it is different for TES4 and other groups...
        size_t loc_datasize = 0;

        if (std::string(loc_tmp.grup,loc_tmp.grup + 4*sizeof(uint8_t)) == "TES4")
        {
            loc_datasize = loc_tmp.size;
            group_TES4      = loc_tmp;
            group_TES4.data = new uint8_t[loc_datasize];
            memcpy(group_TES4.data,&rawdata[loc_fptr],loc_datasize);
        }
        else if (std::string(loc_tmp.grup,loc_tmp.grup + 4*sizeof(uint8_t)) == "GRUP" && std::string(loc_tmp.label,loc_tmp.label + 4*sizeof(uint8_t)) == "ARMO")
        {
            loc_datasize = loc_tmp.size - loc_headersize;
            group_ARMO      = loc_tmp;
            group_ARMO.data = new uint8_t[loc_datasize];
            memcpy(group_ARMO.data,&rawdata[loc_fptr],loc_datasize);
        } 
        else
        {
            loc_datasize = loc_tmp.size - loc_headersize;
        }
        loc_fptr += loc_datasize; //record data read, move pointer
    }

    ParseInfo();
    ParseDevices();
}

void DeviousDevices::DeviceMod::ParseInfo()
{
    masters.clear();

    size_t loc_fptr = 0x00000000;
    while ((loc_fptr) < (group_TES4.size))
    {
        FieldHeader loc_field;

        memcpy(&loc_field,&group_TES4.data[loc_fptr],sizeof(FieldHeader));
        loc_fptr += sizeof(FieldHeader); //move file pointer

        const size_t loc_datasize = loc_field.size;
        std::string loc_signature = std::string(loc_field.type,loc_field.type + 4*sizeof(uint8_t));
        if (loc_signature == "MAST")
        {
            if (loc_datasize > 0)
            {
                std::string loc_master = std::string(&group_TES4.data[loc_fptr],&group_TES4.data[loc_fptr + loc_datasize - 1]);
                masters.push_back(loc_master);
            }
        }
        loc_fptr += loc_datasize; //field data read, move pointer
    }
    masters.push_back(name);

    LOG("=== Final masters of mod {}",name)
    for (int i = 0; i < masters.size();i++)
    {
        LOG("{:02X} = {}",i,masters[i])
    }

}

size_t DeviousDevices::DeviceMod::ParseDevices()
{
    size_t loc_fptr     = 0x00000000;
    size_t loc_res      = 0;

    static const size_t loc_headersize = (sizeof(DeviceRecord) - sizeof(uint8_t*));

    while ((loc_fptr + loc_headersize) < group_ARMO.size)
    {
        devicerecords.push_back(std::shared_ptr<DeviceHandle>(new DeviceHandle));

        memcpy(&devicerecords.back()->record,&group_ARMO.data[loc_fptr],loc_headersize);
        loc_fptr += loc_headersize; //move file pointer

        const size_t loc_datasize = devicerecords.back()->record.size;
        devicerecords.back()->record.data = new uint8_t[loc_datasize];

        memcpy(devicerecords.back()->record.data,&group_ARMO.data[loc_fptr],loc_datasize);
        loc_fptr += loc_datasize; //field data read, move pointer

        const uint32_t loc_formID = devicerecords.back()->record.formId;
        const uint8_t  loc_modindex = (loc_formID & 0xFF000000) >> 24;
        const std::string loc_modsource = masters[loc_modindex];

        devicerecords.back()->source = loc_modsource; 

        if (devicerecords.back()->record.flags & 0x00040000) LOG("Form is compressed!")

        RE::TESForm* loc_form = GetForm(devicerecords.back().get());

        if (loc_form != nullptr) 
        {
            devicerecords.back()->LoadVM();
            devicerecords.back()->LoadKeywords();
        }
        else LOG("Could not find Form !!!")

        loc_res++;
    }

    return loc_res;
}

RE::TESForm* DeviousDevices::DeviceMod::GetForm(const DeviceHandle* a_handle)
{
    RE::TESForm* loc_form = RE::TESDataHandler::GetSingleton()->LookupForm(0x00FFFFFF & a_handle->record.formId,a_handle->source);

    return loc_form;
}

RE::TESForm* DeviousDevices::DeviceMod::GetForm(const uint32_t a_formID)
{
    const uint8_t  loc_modindex = (a_formID & 0xFF000000) >> 24;
    const std::string loc_modsource = masters[loc_modindex];
    RE::TESForm* loc_form = RE::TESDataHandler::GetSingleton()->LookupForm(0x00FFFFFF & a_formID,loc_modsource);
    return loc_form;
}

void DeviousDevices::DeviceHandle::LoadVM()
{
    size_t loc_fptr = 0x00000000;
    while ((loc_fptr) < (record.size))
    {
        FieldHeader loc_field;
        memcpy(&loc_field,&record.data[loc_fptr],sizeof(FieldHeader));
        loc_fptr += sizeof(FieldHeader); //move file pointer

        const size_t loc_datasize = loc_field.size;
        std::string loc_signature = std::string(loc_field.type,loc_field.type + 4*sizeof(uint8_t));
        if (loc_signature == "VMAD") //we only care about VMAD
        {
            static const size_t loc_VMheadersize = 6;
            memcpy(&scripts,&record.data[loc_fptr],loc_VMheadersize);
            loc_fptr += loc_VMheadersize;
            for (int i = 0; i < scripts.scriptCount; i++)
            {
                scripts.scripts.push_back(std::unique_ptr<Script>(new Script()));
                Script* loc_script = scripts.scripts.back().get();

                //parse script name
                uint16_t loc_wscriptsize = *reinterpret_cast<uint16_t*>(&record.data[loc_fptr]);
                std::string loc_scriptname = std::string(&record.data[loc_fptr + 2],&record.data[loc_fptr + 2 + loc_wscriptsize]);
                loc_script->scriptName = loc_scriptname;

                loc_fptr += 2 + loc_wscriptsize;

                //parse script status
                loc_script->status = record.data[loc_fptr];
                loc_fptr += 1;

                //parse property count
                loc_script->propertyCount = *reinterpret_cast<uint16_t*>(&record.data[loc_fptr]);
                loc_fptr += 2;

                //parse properties
                for (int p = 0; p < loc_script->propertyCount; p++)
                {
                    loc_script->properties.push_back(std::unique_ptr<Property>(new Property()));
                    Property* loc_property = loc_script->properties.back().get();

                    static const size_t loc_propertyheadersize = sizeof(Property) - sizeof(std::unique_ptr<uint8_t>);

                    //parse property name
                    uint16_t loc_wpropertysize = *reinterpret_cast<uint16_t*>(&record.data[loc_fptr]);
                    std::string loc_propertyname = std::string(&record.data[loc_fptr + 2],&record.data[loc_fptr + 2 + loc_wpropertysize]);
                    loc_property->propertyName = loc_propertyname;
                    loc_fptr += 2 + loc_wpropertysize;

                    //parse property type
                    loc_property->propertyType = record.data[loc_fptr];
                    loc_fptr += 1;

                    //parse status
                    loc_property->status = record.data[loc_fptr];
                    loc_fptr += 1;

                    //parse raw property data
                    switch(static_cast<Property::PropertyTypes>(loc_property->propertyType))
                    {
                        case Property::PropertyTypes::kObject:
                            {
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[8]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],8);
                                loc_fptr += 8;
                            }
                            break;
                        case Property::PropertyTypes::kWString:
                            {
                                uint16_t loc_wvaluesize = *reinterpret_cast<uint16_t*>(&record.data[loc_fptr]);
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[2 + loc_wvaluesize]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],2 + loc_wvaluesize);
                                loc_fptr += 2 + loc_wvaluesize;
                            }
                            break;
                        case Property::PropertyTypes::kInt:
                        case Property::PropertyTypes::kFloat:
                            {
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[4]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],4);
                                loc_fptr += 4;
                            }
                            break;
                        case Property::PropertyTypes::kBool:
                            {
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[1]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],1);
                                loc_fptr += 1;
                            }
                            break;
                        case Property::PropertyTypes::kArrayObject:
                            {
                                const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&record.data[loc_fptr]);
                                const uint32_t loc_varsize = 4 + loc_arraysize*8;
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[loc_varsize]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],loc_varsize);
                                loc_fptr += loc_varsize;
                            }
                            break;
                        case Property::PropertyTypes::kArrayWString:
                            {
                                //we are entering pain area
                                const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&record.data[loc_fptr]);
                                uint32_t loc_fptr2 = loc_fptr;
                                loc_fptr2 += 4;
                                for (int v = 0; v < loc_arraysize; v++)
                                {
                                    uint16_t loc_wvaluesize = *reinterpret_cast<uint16_t*>(&record.data[loc_fptr2]);
                                    loc_fptr2 += 2 + loc_wvaluesize;
                                }
                                const uint32_t loc_size = loc_fptr2 - loc_fptr;
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[loc_size]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],loc_size);
                                loc_fptr = loc_fptr2;
                            }
                            break;
                        case Property::PropertyTypes::kArrayInt:
                        case Property::PropertyTypes::kArrayFloat:
                            {
                                const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&record.data[loc_fptr]);
                                const uint32_t loc_varsize = 4 + loc_arraysize*4;
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[loc_varsize]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],loc_varsize);
                                loc_fptr += loc_varsize;
                            }
                            break;
                        case Property::PropertyTypes::kArrayBool:
                            {
                                const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&record.data[loc_fptr]);
                                const uint32_t loc_varsize = 4 + loc_arraysize*1;
                                loc_property->data = std::unique_ptr<uint8_t>(new uint8_t[loc_varsize]);
                                memcpy(loc_property->data.get(),&record.data[loc_fptr],loc_varsize);
                                loc_fptr += loc_varsize;
                            }
                            break;
                    }
                }
            }
            break;
        }
        loc_fptr += loc_datasize; //field data read, move pointer
    }
}

void DeviousDevices::DeviceHandle::LoadKeywords()
{
    size_t loc_fptr = 0x00000000;
    while ((loc_fptr) < (record.size))
    {
        FieldHeader loc_field;
        memcpy(&loc_field,&record.data[loc_fptr],sizeof(FieldHeader));
        loc_fptr += sizeof(FieldHeader); //move file pointer

        const size_t loc_datasize = loc_field.size;
        std::string loc_signature = std::string(loc_field.type,loc_field.type + 4*sizeof(uint8_t));
        if (loc_signature == "KSIZ") //we only care about KSIZ
        {
            keywords.ksiz.header = loc_field;
            keywords.ksiz.keywordcount = *reinterpret_cast<uint32_t*>(&record.data[loc_fptr]);
        }  
        else if (loc_signature == "KWDA")   
        {
            keywords.kwda.header = loc_field;
            keywords.kwda.data = std::shared_ptr<uint32_t>(new uint32_t[keywords.ksiz.keywordcount]);  //1 kw = uint32_t
            memcpy(keywords.kwda.data.get(),&record.data[loc_fptr],keywords.kwda.header.size);
            break; //break loop after KWDA as we don't need any more fields
        }

        loc_fptr += loc_datasize; //field data read, move pointer
    }
}

std::pair<std::shared_ptr<uint8_t>, uint8_t> DeviousDevices::DeviceHandle::GetPropertyRaw(std::string a_name)
{
    for (auto && it1 : scripts.scripts)
    {
        for (auto && it2 : it1->properties)
        {
            std::string loc_propertyname = it2->propertyName;

            //check in lower case
            transform(loc_propertyname.begin(), loc_propertyname.end(), loc_propertyname.begin(), ::tolower);
            transform(a_name.begin(), a_name.end(), a_name.begin(), ::tolower);

            if (loc_propertyname == a_name)
            {
                return std::pair<std::shared_ptr<uint8_t>, uint8_t>(it2->data,it2->propertyType);
            }
        }
    }
    return std::pair<std::shared_ptr<uint8_t>, uint8_t>(nullptr,0);
}

uint32_t DeviousDevices::DeviceHandle::GetPropertyOBJ(std::string a_name,bool a_silence)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kObject)
        {
            return *reinterpret_cast<uint32_t*>(loc_property.first.get() + 4U);
        }
        else
        {
            if (!a_silence) LOG("ERROR: Property {} is of incorrect type. Type = {}",a_name,loc_property.second)
            return 0x00000000;
        }
    }
    else
    {
        if (!a_silence) LOG("ERROR: Could not find property {}",a_name)
        return 0x00000000;
    }
}

int32_t DeviousDevices::DeviceHandle::GetPropertyINT(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kInt)
        {
            return *reinterpret_cast<int32_t*>(loc_property.first.get());
        }
        else
        {
            LOG("ERROR: Property {} is of incorrect type. Type = {:02}",a_name,loc_property.second)
            return 0x00000000;
        }
    }
    else
    {
        LOG("ERROR: Could not find property {}",a_name)
        return 0x00000000;
    }
}

float DeviousDevices::DeviceHandle::GetPropertyFLT(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kFloat)
        {
            return *reinterpret_cast<float*>(loc_property.first.get());
        }
        else
        {
            LOG("ERROR: Property {} is of incorrect type. Type = {:02}",a_name,loc_property.second)
            return 0.0f;
        }
    }
    else
    {
        LOG("ERROR: Could not find property {}",a_name)
        return 0.0f;
    }
}

bool DeviousDevices::DeviceHandle::GetPropertyBOL(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kBool)
        {
            return *reinterpret_cast<bool*>(loc_property.first.get());
        }
        else
        {
            LOG("ERROR: Property {} is of incorrect type. Type = {:02}",a_name,loc_property.second)
            return false;
        }
    }
    else
    {
        LOG("ERROR: Could not find property {}",a_name)
        return false;
    }
}

std::vector<uint32_t> DeviousDevices::DeviceHandle::GetPropertyOBJA(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kArrayObject)
        {
            std::vector<uint32_t> loc_res;
            uint32_t loc_fptr = 0x00000000;
            const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&loc_property.first.get()[loc_fptr]);
            loc_fptr += 4;

            struct PropertyObject
            {
                uint16_t unk1;
                uint16_t alias;
                uint32_t formId;
            };

            for (size_t i = 0; i < loc_arraysize; i++)
            {
                  PropertyObject loc_object = *reinterpret_cast<PropertyObject*>(&loc_property.first.get()[loc_fptr]);
                  loc_res.push_back(loc_object.formId);
                  loc_fptr += sizeof(PropertyObject);
            }

            return loc_res;
        }
        else
        {
            return std::vector<uint32_t>();
        }
    }
    else
    {
        return std::vector<uint32_t>();
    }
}

std::vector<int32_t> DeviousDevices::DeviceHandle::GetPropertyINTA(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kArrayInt)
        {
            std::vector<int32_t> loc_res;
            uint32_t loc_fptr = 0x00000000;
            const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&loc_property.first.get()[loc_fptr]);
            loc_fptr += 4;

            for (size_t i = 0; i < loc_arraysize; i++)
            {
                  int32_t loc_val = *reinterpret_cast<int32_t*>(&loc_property.first.get()[loc_fptr]);
                  loc_res.push_back(loc_val);
                  loc_fptr += sizeof(int32_t);
            }

            return loc_res;
        }
        else
        {
            return std::vector<int32_t>();
        }
    }
    else
    {
        return std::vector<int32_t>();
    }
}

std::vector<float> DeviousDevices::DeviceHandle::GetPropertyFLTA(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kArrayFloat)
        {
            std::vector<float> loc_res;
            uint32_t loc_fptr = 0x00000000;
            const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&loc_property.first.get()[loc_fptr]);
            loc_fptr += 4;

            for (size_t i = 0; i < loc_arraysize; i++)
            {
                  float loc_val = *reinterpret_cast<float*>(&loc_property.first.get()[loc_fptr]);
                  loc_res.push_back(loc_val);
                  loc_fptr += sizeof(float);
            }

            return loc_res;
        }
        else
        {
            return std::vector<float>();
        }
    }
    else
    {
        return std::vector<float>();
    }
}

std::vector<bool> DeviousDevices::DeviceHandle::GetPropertyBOLA(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kArrayFloat)
        {
            std::vector<bool> loc_res;
            uint32_t loc_fptr = 0x00000000;
            const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&loc_property.first.get()[loc_fptr]);
            loc_fptr += 4;

            for (size_t i = 0; i < loc_arraysize; i++)
            {
                  float loc_val = *reinterpret_cast<bool*>(&loc_property.first.get()[loc_fptr]);
                  loc_res.push_back(loc_val);
                  loc_fptr += sizeof(bool);
            }

            return loc_res;
        }
        else
        {
            return std::vector<bool>();
        }
    }
    else
    {
        return std::vector<bool>();
    }
}

std::string DeviousDevices::DeviceHandle::GetPropertySTR(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kWString)
        {
            uint16_t loc_wsize = *reinterpret_cast<uint16_t*>(loc_property.first.get());
            std::string loc_res = std::string(loc_property.first.get() + 2, loc_property.first.get() + 2 + loc_wsize); //convert wstring to zstring
            return loc_res;
        }
        else
        {
            LOG("ERROR: Property {} is of incorrect type. Type = {:02}",a_name,loc_property.second)
            return "";
        }
    }
    else
    {
        LOG("ERROR: Could not find property {}",a_name)
        return "";
    }
}

std::vector<std::string> DeviousDevices::DeviceHandle::GetPropertySTRA(std::string a_name)
{
    auto loc_property = GetPropertyRaw(a_name);
    if (loc_property.first != nullptr)
    {
        if (loc_property.second == (uint8_t)Property::PropertyTypes::kArrayWString)
        {
            std::vector<std::string> loc_res;
            uint8_t* loc_data = loc_property.first.get();

            uint32_t loc_fptr = 0x00000000;
            const uint32_t loc_arraysize = *reinterpret_cast<uint32_t*>(&loc_data[loc_fptr]);
            loc_fptr += 4;

            for (size_t i = 0; i < loc_arraysize; i++)
            {
                const uint16_t loc_wsize = *reinterpret_cast<uint16_t*>(&loc_data[loc_fptr]);
                const std::string loc_val = std::string(&loc_data[loc_fptr] + 2, &loc_data[loc_fptr] + 2 + loc_wsize); //convert wstring to zstring
                loc_res.push_back(loc_val);
                loc_fptr += 2 + loc_wsize;
            }

            return loc_res;
        }
        else
        {
            return std::vector<std::string>();
        }
    }
    else
    {
        return std::vector<std::string>();
    }
}

RE::TESObjectARMO* DeviousDevices::GetRenderDevice(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice)
{
    RE::TESObjectARMO* loc_res = DeviceReader::GetSingleton()->GetDeviceRender(a_invdevice);

    if (loc_res == nullptr)
    {
        LOG("ERROR: Cant find device {}",a_invdevice->GetName())
    }
    else
    {
        LOG("GetRenderDevice({} 0x{:08X}) called - Result = {:X} ",a_invdevice->GetName(),a_invdevice->GetFormID(),loc_res->GetFormID())
    }

    return loc_res;
}

RE::TESObjectARMO* DeviousDevices::GetDeviceByName(PAPYRUSFUNCHANDLE, std::string a_name)
{
    auto loc_reader = DeviceReader::GetSingleton();
    auto loc_unit = loc_reader->GetDeviceUnit(a_name);
    return loc_unit.deviceInventory;
}

RE::TESForm* DeviousDevices::GetPropertyForm(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        uint32_t loc_formID = loc_handle->GetPropertyOBJ(a_propertyname,false);
        
        //we need to convert it to correct ID and get the form
        if (loc_formID > 0)
        {
            RE::TESForm* loc_form = loc_unit.deviceMod->GetForm(loc_formID);
            if (loc_form != nullptr) 
            {   
                LOG("GetPropertyForm({} 0x{:08X} , {}) called - Result = {:X} ",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname,loc_form->GetFormID())
                return loc_form;
            } 
            else LOG("!!!Form 0x{:08X} not found!!!",loc_formID)
        }

    }
    return nullptr;
}

int DeviousDevices::GetPropertyInt(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        int loc_res = loc_handle->GetPropertyINT(a_propertyname);
        LOG("GetPropertyInt({} 0x{:08X} , {}) called - Result = {} ",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname,loc_res)
        return loc_res;
    }
    return 0;
}

float DeviousDevices::GetPropertyFloat(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        float loc_res = loc_handle->GetPropertyFLT(a_propertyname);
        LOG("GetPropertyFloat({} 0x{:08X} , {}) called - Result = {} ",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname,loc_res)
        return loc_res;
    }
    return 0.0;
}

bool DeviousDevices::GetPropertyBool(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        bool loc_res = loc_handle->GetPropertyBOL(a_propertyname);
        LOG("GetPropertyBool({} 0x{:08X} , {}) called - Result = {} ",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname,loc_res)
        return loc_res;
    }
    return false;
}

std::string DeviousDevices::GetPropertyString(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::string loc_res = loc_handle->GetPropertySTR(a_propertyname);
        LOG("GetPropertyString({} 0x{:08X} , {}) called - Result = {} ",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname,loc_res)
        return loc_res;
    }
    return "";
}

std::vector<RE::TESForm*> DeviousDevices::GetPropertyFormArray(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::vector<uint32_t> loc_formIDs = loc_handle->GetPropertyOBJA(a_propertyname);
        std::vector<RE::TESForm*> loc_res;
        //we need to convert it to correct ID and get the form
        if (loc_formIDs.size() > 0)
        {

            for(auto&& it : loc_formIDs)
            {
                if (it > 0)
                {
                    RE::TESForm* loc_form = loc_unit.deviceMod->GetForm(it);
                    loc_res.push_back(loc_form);
                }
                else loc_res.push_back(nullptr);
            }

            LOG("GetPropertyFormArray({} 0x{:08X} , {}) called - Result¨:",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname)
            for (auto&& it2 : loc_res) LOG("\t0x{:08X} - {}",it2->GetFormID(),it2->GetName())

            return loc_res;
        }
    }
    return std::vector<RE::TESForm*>();
}

std::vector<int> DeviousDevices::GetPropertyIntArray(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::vector<int> loc_res = loc_handle->GetPropertyINTA(a_propertyname);
        LOG("GetPropertyIntArray({} 0x{:08X} , {}) called - Result¨:",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname)
        for (auto&& it2 : loc_res) LOG("\t{}",it2)
        return loc_res;
    }
    return std::vector<int>();
}

std::vector<float> DeviousDevices::GetPropertyFloatArray(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::vector<float> loc_res = loc_handle->GetPropertyFLTA(a_propertyname);
        LOG("GetPropertyFloatArray({} 0x{:08X} , {}) called - Result¨:",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname)
        for (auto&& it2 : loc_res) LOG("\t{}",it2)
        return loc_res;
    }
    return std::vector<float>();
}

std::vector<bool> DeviousDevices::GetPropertyBoolArray(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::vector<bool> loc_res = loc_handle->GetPropertyBOLA(a_propertyname);
        LOG("GetPropertyBoolArray({} 0x{:08X} , {}) called - Result¨:",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname)
        for (auto&& it2 : loc_res) LOG("\t{}",it2)
        return loc_res;
    }
    return std::vector<bool>();
}

std::vector<std::string> DeviousDevices::GetPropertyStringArray(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice, std::string a_propertyname, int a_mode)
{
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);
    auto loc_handle = (a_mode == 0) ? loc_unit.deviceHandle : loc_unit.history.front().deviceHandle;
    
    if (loc_handle != nullptr)
    {
        std::vector<std::string> loc_res = loc_handle->GetPropertySTRA(a_propertyname);
        LOG("GetPropertyStringArray({} 0x{:08X} , {}) called - Result:",a_invdevice->GetName(),a_invdevice->GetFormID(),a_propertyname)
        for (auto&& it2 : loc_res) LOG("\t{}",it2)
        return loc_res;
    }
    return std::vector<std::string>();
}

std::vector<std::string> DeviousDevices::GetEditingMods(PAPYRUSFUNCHANDLE, RE::TESObjectARMO* a_invdevice)
{
    std::vector<std::string> loc_res;
    auto loc_unit   = DeviceReader::GetSingleton()->GetDeviceUnit(a_invdevice);

    for (auto&& it : loc_unit.history) loc_res.push_back(it.deviceMod->name);

    return loc_res;
}
