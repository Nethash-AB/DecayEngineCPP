#include "Exception/ArgumentException.hpp"

using namespace DecFramework::Exception;

ArgumentException::ArgumentException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile)
    : Message(std::move(message)), ParamName(),
    EngineException(nullptr, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentException::ArgumentException(std::string message, std::string paramName, int lineNumber, std::string callerFunction, std::string sourceFile)
    : Message(std::move(message)), ParamName(std::move(paramName)),
    EngineException(nullptr, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentException::ArgumentException(std::string message, std::string paramName, EngineException* innerException,
    int lineNumber, std::string callerFunction, std::string sourceFile)
    : Message(std::move(message)), ParamName(std::move(paramName)),
    EngineException(innerException, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentException::~ArgumentException() = default;

[[nodiscard]] const char* ArgumentException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(ArgumentException) << ": " << Message;
    if (ParamName.length() > 0)
    {
        stream << " | In parameter: " << ParamName << ".";
    }
    stream << " | " << GetStackTraceLocation();

    return stream.str().c_str();
}