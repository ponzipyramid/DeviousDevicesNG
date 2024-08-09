#include "Papyrus.h"
#include "Hooks.h"
#include "Hider.h"
#include "NodeHider.h"
#include "UpdateManager.h"
#include "DeviceReader.h"
#include "Settings.h"
#include "LibFunctions.h"
#include "Serialization.h"
#include "HooksVirtual.h"
#include <stddef.h>
#include "API.h"

#if (DD_USEINVENTORYFILTER_S == 1U)
    #include "InventoryFilter.h"
#endif

using namespace RE::BSScript;
using namespace SKSE;
using namespace SKSE::stl;
 
namespace {
    void InitializeLogging() 
    {
        auto logsFolder = SKSE::log::log_directory();
        if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
        auto logFilePath = *logsFolder / "DeviousDevicesNG.log";
        std::shared_ptr<spdlog::logger> loggerPtr;
        if (IsDebuggerPresent()) 
        {
            loggerPtr = std::make_shared<spdlog::logger>("log", std::make_shared<spdlog::sinks::msvc_sink_mt>());
        } 
        else 
        {
            loggerPtr = std::make_shared<spdlog::logger>("log", std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true));
        }
        spdlog::set_default_logger(std::move(loggerPtr));
        spdlog::set_level(spdlog::level::trace);
        spdlog::flush_on(spdlog::level::trace);
        DEBUG("Logging set - Log gfile = {}",logFilePath.string())
    }

    void InitializePapyrus() 
    {
        //log::trace("Initializing Papyrus binding...");
        if (GetPapyrusInterface()->Register(DeviousDevices::RegisterFunctions)) 
        {
            DEBUG("Papyrus functions bound.");
        } 
        else 
        {
            stl::report_and_fail("Failure to register Papyrus bindings.");
        }
    }

    void InitializeMessaging() 
    {
        const auto g_messaging = GetMessagingInterface();
        if (!g_messaging->RegisterListener([](MessagingInterface::Message* message) 
        {
            switch (message->type) 
            {
                // Skyrim lifecycle events.
                case MessagingInterface::kPostPostLoad:  // Called after all plugins have finished running
                    DeviousDevices::Hooks::Install();
                    break;
                case MessagingInterface::kInputLoaded:  // Called when all game data has been found.
                    break;
                case MessagingInterface::kDataLoaded:  // All ESM/ESL/ESP plugins have loaded, main menu is now
                                                        // active.  
                    DeviousDevices::DeviceHiderManager::GetSingleton()->Setup();
                    DeviousDevices::LibFunctions::GetSingleton()->Setup();
                    DeviousDevices::DeviceReader::GetSingleton()->Setup();
                    DeviousDevices::InventoryFilter::GetSingleton()->Setup();
                    DeviousDevices::NodeHider::GetSingleton()->Setup();
                    DeviousDevices::UpdateManager::GetSingleton()->Setup();
                    DeviousDevices::ExpressionManager::GetSingleton()->Setup();
                    DeviousDevices::HooksVirtual::GetSingleton()->Setup();
                    if (!DeviousDevicesAPI::g_API) DeviousDevicesAPI::g_API = new DeviousDevicesAPI::DeviousDevicesAPI;
                    break;
                case MessagingInterface::kPostLoadGame:  // Player's selected save game has finished loading.
                                                            // Data will be a boolean indicating whether the load was
                                                            // successful.
                case MessagingInterface::kNewGame: //also when player makes new game, as kPostLoadGame event is called too late on new game
                    break;
            }
        })) 
        {
            stl::report_and_fail("Unable to register message listener.");
        }

        if (!g_messaging->RegisterListener(NULL,[](MessagingInterface::Message* message) 
        {
            switch (message->type) 
            {
                // Request for api received
                case DD_APITYPEKEY:
                    message->dataLen = sizeof(DeviousDevicesAPI::DeviousDevicesAPI*);
                    *(DeviousDevicesAPI::DeviousDevicesAPI**)message->data = DeviousDevicesAPI::g_API;
                    break;
            }
        })) 
        {
            stl::report_and_fail("Unable to register message listener.");
        }
    }

    void InitializeSerialization() {
        DEBUG("Initializing cosave serialization...");
        auto* loc_serde = SKSE::GetSerializationInterface();
        loc_serde->SetUniqueID(_byteswap_ulong('DDNG'));
        loc_serde->SetSaveCallback(DeviousDevices::OnGameSaved);
        loc_serde->SetRevertCallback(DeviousDevices::OnRevert);
        loc_serde->SetLoadCallback(DeviousDevices::OnGameLoaded);
        DEBUG("Cosave serialization initialized.");
    }
}

SKSEPluginLoad(const LoadInterface* skse) 
{
    SKSE::Init(skse);

    InitializeLogging();
    DeviousDevices::ConfigManager::GetSingleton()->Setup();

    InitializePapyrus();
    InitializeMessaging();
    InitializeSerialization();

    return true;
}
