#include "Exception/FormatException.hpp"

using namespace DecFramework::Exception;

FormatException::FormatException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile)
    : _message(std::move(message)), EngineException(nullptr, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

FormatException::FormatException(std::string message, EngineException* innerException, int lineNumber, std::string callerFunction, std::string sourceFile)
    : _message(std::move(message)), EngineException(innerException, lineNumber, std::move(callerFunction), std::move(sourceFile))
{
}

[[nodiscard]] const char* FormatException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(FormatException) << ": " << _message << ". | " << GetStackTraceLocation();

    return stream.str().c_str();
}