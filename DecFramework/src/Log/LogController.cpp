#include "Log/LogController.hpp"

using namespace DecFramework;
using namespace DecFramework::Log;

LogController::LogController(IGlobalEnvironment* gEnv)
    : _gEnv(gEnv), _loggers()
{
}

LogController::~LogController()
{
    for (auto logger : _loggers)
    {
        delete logger;
    }
}

void LogController::Print(const LogMessage& message)
{
    for (auto logger : _loggers)
    {
        if (logger->HandledSeverityLevels & message.Severity)
        {
            logger->AddMessage(message);
        }
    }
}