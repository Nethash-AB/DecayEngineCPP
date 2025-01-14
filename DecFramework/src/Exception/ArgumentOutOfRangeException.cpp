#include "Exception/ArgumentOutOfRangeException.hpp"

using namespace DecFramework::Exception;

ArgumentOutOfRangeException::ArgumentOutOfRangeException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile)
    : ArgumentException(std::move(message), lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(std::string message, std::string paramName,
    int lineNumber, std::string callerFunction, std::string sourceFile)
    : ArgumentException(std::move(message), std::move(paramName), lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(std::string message, std::string paramName, EngineException* innerException,
    int lineNumber, std::string callerFunction, std::string sourceFile)
    : ArgumentException(std::move(message), std::move(paramName), innerException, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

ArgumentOutOfRangeException::~ArgumentOutOfRangeException() = default;

[[nodiscard]] const char* ArgumentOutOfRangeException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(ArgumentOutOfRangeException) << ": " << Message;
    if (ParamName.length() > 0)
    {
        stream << " | In parameter: " << ParamName << ".";
    }
    stream << " | " << GetStackTraceLocation();

    return stream.str().c_str();
}