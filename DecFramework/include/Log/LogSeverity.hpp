#ifndef DECAYENGINE_LOGSEVERITY_HPP
#define DECAYENGINE_LOGSEVERITY_HPP

#include "EngineSdk.hpp"

namespace DecFramework::Log
{
    enum struct LogSeverity : log_severity_t
    {
        Disabled,
        Debug,
        Info,
        Warning,
        Error,
        CriticalError,
        _
    };

    inline std::string GetLogSeverityName(const LogSeverity& logSeverity)
    {
        switch (logSeverity)
        {
            case LogSeverity::Debug:
                return "Debug";
            case LogSeverity::Info:
                return "Info";
            case LogSeverity::Warning:
                return "Warning";
            case LogSeverity::Error:
                return "Error";
            case LogSeverity::CriticalError:
                return "CriticalError";
            default:
                return "Disabled";
        }
    }

    inline std::ostream& operator<<(std::ostream& lhs, const LogSeverity& rhs)
    {
        return lhs << GetLogSeverityName(rhs);
    }
}

#endif //DECAYENGINE_LOGSEVERITY_HPP
