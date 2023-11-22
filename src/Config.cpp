#include <Config.h>

using DeviousDevices::ConfigManager;

SINGLETONBODY(ConfigManager)

void ConfigManager::Setup()
{
    _config = boost::property_tree::ptree();
    try
    {
        boost::property_tree::ini_parser::read_ini("Data\\skse\\plugins\\DeviousDevices.ini", _config);
    }
    catch( std::exception &ex )
    {
        WARN("ERROR LOADING ini FILE: {}",ex.what())
        return;
    }

    //clean catche, so if game is relaoded, the catche will be also reloaded
    for (auto&& it : _catche) delete it.second;
    _catche.clear();
}

std::vector<std::string> ConfigManager::GetArrayRaw(std::string a_name, std::string a_sep) const
{
    std::vector<std::string> loc_res;
    boost::split(loc_res,_config.get<std::string>(a_name),boost::is_any_of(a_sep));

    //remove additional spaces, and made the words lower case
    for (auto&& it : loc_res) 
    {
        const auto loc_first = it.find_first_not_of(' ');
        const auto loc_last  = it.find_last_not_of(' ');
        it = it.substr(loc_first,loc_last - loc_first + 1);
        std::transform(it.begin(), it.end(), it.begin(), ::tolower);
    }

    return loc_res;
}

template<typename T>
T ConfigManager::GetVariable(std::string a_name) const
{
    void* loc_cres = _catche[a_name];
    if (loc_cres != nullptr) return *(T*)loc_cres;

    T loc_res = _config.get<T>(a_name);
    _catche[a_name] = new T(loc_res);

    return loc_res;
}

template<typename T>
std::vector<T> ConfigManager::GetArray(std::string a_name, std::string a_sep) const
{
    void* loc_cres = _catche[a_name];
    if (loc_cres != nullptr) return *(std::vector<T>*)loc_cres;

    std::vector<std::string> loc_raw = GetArrayRaw(a_name,a_sep);
    std::vector<T> loc_res;

    for (auto&&it : loc_raw)
    {
        if (it != "") loc_res.push_back(boost::lexical_cast<T>(it));
    }

    _catche[a_name] = new std::vector<T>(loc_res);

    return loc_res;
}

template int ConfigManager::GetVariable<int>(std::string a_name) const;
template std::string ConfigManager::GetVariable<std::string>(std::string a_name) const;
template float ConfigManager::GetVariable<float>(std::string a_name) const;
template int ConfigManager::GetVariable<int>(std::string a_name) const;

template std::vector<int> ConfigManager::GetArray<int>(std::string a_name, std::string a_sep) const;
template std::vector<std::string> ConfigManager::GetArray<std::string>(std::string a_name, std::string a_sep) const;
template std::vector<float> ConfigManager::GetArray<float>(std::string a_name, std::string a_sep) const;
template std::vector<int> ConfigManager::GetArray<int>(std::string a_name, std::string a_sep) const;