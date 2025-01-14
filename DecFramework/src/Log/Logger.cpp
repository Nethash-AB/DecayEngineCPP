#include "Log/Logger.hpp"

#include <utility>

using namespace DecFramework;
using namespace DecFramework::Log;

LogMessage::LogMessage(SubSystem::subsystem_id_t subSystemId, const LogSeverity& severity, std::string message, CURRENT_LOCATION_DECL())
    : SubSystemId(subSystemId), Severity(severity), Message(std::move(message)),
    LineNumber(lineNumber), CallerFunction(std::move(callerFunction)), SourceFile(std::move(sourceFile))
{
}

Logger::Logger(IGlobalEnvironment* gEnv)
    : GEnv(gEnv), HandledSeverityLevels(LogSeverity::Disabled)
{
}

Logger::~Logger() = default;