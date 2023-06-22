#include "Papyrus.h"
#include <stddef.h>

using namespace RE::BSScript;
using namespace SKSE;
using namespace SKSE::log;
using namespace SKSE::stl;
 
namespace {
    void InitializeLogging() {
        auto path = log_directory();
        if (!path) {
            report_and_fail("Unable to lookup SKSE logs directory.");
        }
        *path += L"/DDi.log";

        std::shared_ptr<spdlog::logger> log;
        if (IsDebuggerPresent()) {
            log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
        } else {
            log = std::make_shared<spdlog::logger>(
                "Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
        }
        log->set_level(spdlog::level::from_str("info"));
        log->flush_on(spdlog::level::from_str("trace"));

        spdlog::set_default_logger(std::move(log));
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] %v");
    }

    void InitializePapyrus() {
        log::trace("Initializing Papyrus binding...");
        if (GetPapyrusInterface()->Register(DeviousDevices::RegisterFunctions)) {
            log::info("Papyrus functions bound.");
        } else {
            stl::report_and_fail("Failure to register Papyrus bindings.");
        }
    }
}

SKSEPluginLoad(const LoadInterface* skse) {
    InitializeLogging();

    auto* plugin = PluginDeclaration::GetSingleton();
    auto version = plugin->GetVersion();
    log::info("{} {} is loading...", plugin->GetName(), version);

    Init(skse);
    InitializePapyrus();

    log::info("{} has finished loading.", plugin->GetName());
    return true;
}
