#include "varak/core/log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Varak {

    Ref<spdlog::logger> Log::s_coreLogger;
    Ref<spdlog::logger> Log::s_clientLogger;

    void Log::init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Varak.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_coreLogger = createRef<spdlog::logger>("VARAK", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_coreLogger);
        s_coreLogger->set_level(spdlog::level::trace);
        s_coreLogger->flush_on(spdlog::level::trace);

        s_clientLogger = createRef<spdlog::logger>("APP", begin(logSinks), end(logSinks));
        spdlog::register_logger(s_clientLogger);
        s_clientLogger->set_level(spdlog::level::trace);
        s_clientLogger->flush_on(spdlog::level::trace);
    }

} // namespace Varak
