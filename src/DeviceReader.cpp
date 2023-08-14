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
    return _database[a_invdevice];
}

void DeviousDevices::DeviceReader::LoadDDMods()
{
    LOG("Checking DD mods")

    _ddmods.clear();

    RE::BSSimpleList<RE::TESFile*>* loc_filelist = &RE::TESDataHandler::GetSingleton()->files;
    RE::TESFile* loc_DDA;

    std::array<std::string,4> loc_masters = {"Devious Devices - Assets.esm","Devious Devices - Integration.esm","Devious Devices - Expansion.esm","Devious Devices - Contraptions.esm"};
    
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
    LOG("=== DD mods found: {}",_ddmods.size())
    for(auto && it : _ddmods) LOG("{}",it->GetFilename())
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
            _ddmodspars.push_back(std::unique_ptr<DeviceMod>(new DeviceMod(std::string(it->GetFilename()),loc_rawdata,loc_size)));
        }
        else LOG("Failed to open file {}",it->GetFilename())
    }
}

void DeviousDevices::DeviceReader::LoadDB()
{
    LOG("=== Building database")
    for (auto && it1 : _ddmodspars)
    {
        //LOG("Checking devices in mod {}",it1->name)
        for (auto && it2 : it1->devicerecords)
        {
            uint32_t loc_formid1 = it2->GetProperty("deviceInventory");
            uint32_t loc_formid2 = it2->GetProperty("deviceRendered");
            //LOG("FormID {} , {} found",loc_formid1,loc_formid2)
            if (loc_formid1 > 0 && loc_formid2 > 0)
            {
                RE::TESObjectARMO* loc_ID = reinterpret_cast<RE::TESObjectARMO*>(it1->GetForm(loc_formid1));
                RE::TESObjectARMO* loc_RD = reinterpret_cast<RE::TESObjectARMO*>(it1->GetForm(loc_formid2));
                if (loc_ID && loc_RD) 
                {   
                    //LOG("Device {} , {:X} found",loc_ID->GetName(),loc_RD->GetFormID())
                    _database[loc_ID] = loc_RD;
                } 
                else LOG("!!!Device not found!!!")
            }
        }
    }

    LOG("=== Building database DONE - Size = {}",_database.size())
    for (auto&& it : _database) LOG("Database entry: 0x{:X} = 0x{:X} ({}) ",it.first->GetFormID(),it.second->GetFormID(),it.first->GetName())
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
            LOG("TES4 group found")
        }
        else if (std::string(loc_tmp.grup,loc_tmp.grup + 4*sizeof(uint8_t)) == "GRUP" && std::string(loc_tmp.label,loc_tmp.label + 4*sizeof(uint8_t)) == "ARMO")
        {
            loc_datasize = loc_tmp.size - loc_headersize;
            group_ARMO      = loc_tmp;
            group_ARMO.data = new uint8_t[loc_datasize];
            memcpy(group_ARMO.data,&rawdata[loc_fptr],loc_datasize);
            LOG("ARMO group found")
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
        LOG("{:X} = {}",i,masters[i])
    }

}

size_t DeviousDevices::DeviceMod::ParseDevices()
{
    size_t loc_fptr     = 0x00000000;
    size_t loc_res      = 0;

    static const size_t loc_headersize = (sizeof(DeviceRecord) - sizeof(uint8_t*));

    while ((loc_fptr + loc_headersize) < group_ARMO.size)
    {
        devicerecords.push_back(std::unique_ptr<DeviceHandle>(new DeviceHandle));

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
        }
        loc_fptr += loc_datasize; //field data read, move pointer
    }
}

uint32_t DeviousDevices::DeviceHandle::GetProperty(std::string a_name)
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
                //LOG("Raw property data {}",*reinterpret_cast<uint64_t*>(it2->data.get()))
                return *reinterpret_cast<uint32_t*>(it2->data.get() + 4U);
            }
        }
    }

    return 0x00000000;
}
