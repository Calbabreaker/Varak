#pragma once

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace Varak
{
    class Log
    {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger>& getCoreLogger()
        {
            return s_coreLogger;
        }
        static std::shared_ptr<spdlog::logger>& getClientLogger()
        {
            return s_clientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };

} // namespace Varak

// for only the Varak code
#define VR_CORE_TRACE(...) ::Varak::Log::getCoreLogger()->trace(__VA_ARGS__)
#define VR_CORE_INFO(...) ::Varak::Log::getCoreLogger()->info(__VA_ARGS__)
#define VR_CORE_WARN(...) ::Varak::Log::getCoreLogger()->warn(__VA_ARGS__)
#define VR_CORE_ERROR(...) ::Varak::Log::getCoreLogger()->error(__VA_ARGS__)
#define VR_CORE_CRITICAL(...)                                                  \
    ::Varak::Log::getCoreLogger()->critical(__VA_ARGS__)

// for the client
#define VR_TRACE(...) ::Varak::Log::getClientLogger()->trace(__VA_ARGS__)
#define VR_INFO(...) ::Varak::Log::getClientLogger()->info(__VA_ARGS__)
#define VR_WARN(...) ::Varak::Log::getClientLogger()->warn(__VA_ARGS__)
#define VR_ERROR(...) ::Varak::Log::getClientLogger()->error(__VA_ARGS__)
#define VR_CRITICAL(...) ::Varak::Log::getClientLogger()->critical(__VA_ARGS__)
