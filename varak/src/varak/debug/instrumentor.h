#pragma once

// to enable profiling change value from 0 to 1
#define VR_PROFILE 0

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

#include "varak/core/base.h"

namespace Varak {

    struct ProfileResult
    {
        const std::string name;
        std::chrono::duration<double, std::micro> start;
        std::chrono::microseconds elapsed;
        std::thread::id threadID;
    };

    class Instrumentor
    {
    public:
        void beginSession(const std::string& name, const std::string& filepath)
        {
            std::lock_guard lock(m_mutex);

            if (m_sessionActive)
            {
                VR_CORE_ERROR("Cannot begin session {0} when {1} already active!", name, m_sessionName);
                endSession();
            }

            VR_CORE_INFO("Begin Profiling: {0}", name);

            m_outputStream.open(filepath);
            if (m_outputStream.is_open())
            {
                m_outputStream << std::setprecision(3) << std::fixed;
                m_outputStream << "{\"otherData\": {},\"traceEvents\":[{}";
                m_sessionActive = true;
                m_sessionName = name;
            }
            else
            {
                VR_CORE_ERROR("Instrumentor failed to open file '{0}'!", filepath);
            }
        }

        void endSession()
        {
            std::lock_guard lock(m_mutex);

            if (!m_sessionActive)
            {
                VR_CORE_ERROR("Cannot end session when session has not begun yet!");
                return;
            }

            VR_CORE_INFO("End Profile: {0}", m_sessionName);

            m_outputStream << "]}";
            m_outputStream.flush();
            m_outputStream.close();
            m_sessionActive = false;
        }

        void writeProfile(const ProfileResult& result)
        {
            std::lock_guard lock(m_mutex);

            m_outputStream << ",{";
            m_outputStream << "\"cat\":\"function\",";
            m_outputStream << "\"dur\":" << (result.elapsed.count()) << ',';
            m_outputStream << "\"name\":\"" << result.name << "\",";
            m_outputStream << "\"ph\":\"X\",";
            m_outputStream << "\"pid\":0,";
            m_outputStream << "\"tid\":" << result.threadID << ",";
            m_outputStream << "\"ts\":" << result.start.count();
            m_outputStream << "}";
        }

        static Instrumentor& get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        Instrumentor() = default;
        ~Instrumentor()
        {
            if (m_sessionActive)
                endSession();
        }

        std::ofstream m_outputStream;
        std::mutex m_mutex;

        bool m_sessionActive = false;
        std::string m_sessionName;
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name) : m_name(name)
        {
            m_startTimepoint = std::chrono::steady_clock::now(); //
        }

        ~InstrumentationTimer()
        {
            if (!m_stopped)
                stop();
        }

        void stop()
        {
            auto endTimepoint = std::chrono::steady_clock::now();

            auto highResStart = std::chrono::duration<double, std::micro>({ m_startTimepoint.time_since_epoch() });
            auto elapsedTime =
                std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() -
                std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch();

            Instrumentor::get().writeProfile({ m_name, highResStart, elapsedTime, std::this_thread::get_id() });

            m_stopped = true;
        }

    private:
        const char* m_name;
        std::chrono::time_point<std::chrono::steady_clock> m_startTimepoint;
        bool m_stopped = false;
    };

} // namespace Varak

#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) ||      \
    defined(__ghs__)
    #define VR_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
    #define VR_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
    #define VR_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
    #define VR_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
    #define VR_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
    #define VR_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
    #define VR_FUNC_SIG __func__
#else
    #error "Function Signature Unknown!"
#endif

#if VR_PROFILE == 1
    #define VR_PROFILE_SCOPE(name) ::Varak::InstrumentationTimer timer##__LINE__(name)
    #define VR_PROFILE_FUNCTION() VR_PROFILE_SCOPE(VR_FUNC_SIG)
    #define VR_PROFILE_BEGIN_SESSION(name, filepath) ::Varak::Instrumentor::get().beginSession(name, filepath)
    #define VR_PROFILE_END_SESSION() ::Varak::Instrumentor::get().endSession()
#else
    #define VR_PROFILE_SCOPE(name)
    #define VR_PROFILE_FUNCTION()
    #define VR_PROFILE_BEGIN_SESSION(name, filepath)
    #define VR_PROFILE_END_SESSION()
#endif
