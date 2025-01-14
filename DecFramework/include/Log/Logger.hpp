#ifndef DECAYENGINE_LOGGER_HPP
#define DECAYENGINE_LOGGER_HPP

#include "Log/LogSeverity.hpp"
#include "EngineSdk.hpp"
#include <type_traits>
#include <string>

FWD_LOG_CONTROLLER()
FWD_GLOBAL_ENVIRONMENT()

namespace DecFramework::Log
{
    struct LogMessage
    {
        public:
            const SubSystem::subsystem_id_t SubSystemId;
            const LogSeverity Severity;
            const std::string Message;
            const int LineNumber;
            const std::string CallerFunction;
            const std::string SourceFile;

            explicit LogMessage(SubSystem::subsystem_id_t subSystemId, const LogSeverity& severity, std::string message, CURRENT_LOCATION_DECL());
            LogMessage(const LogMessage& rhs) = default;
            ~LogMessage() = default;
    };

    class Logger
    {
        public:
            LogSeverityFlags HandledSeverityLevels;
        protected:
            IGlobalEnvironment* GEnv;

            explicit Logger(IGlobalEnvironment* gEnv);
            virtual ~Logger();

            virtual void AddMessage(const LogMessage& message) const = 0;

            friend class DecFramework::Log::LogController;
    };
}

#endif //DECAYENGINE_LOGGER_HPP
