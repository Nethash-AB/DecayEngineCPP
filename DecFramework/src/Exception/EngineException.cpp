#include "Exception/EngineException.hpp"
#include <sstream>

using namespace DecFramework::Exception;

EngineException::EngineException(EngineException* innerException, int lineNumber, std::string callerFunction, std::string sourceFile)
    : InnerException(innerException), LineNumber(lineNumber), CallerFunction(std::move(callerFunction)), SourceFile(std::move(sourceFile))
{
}

EngineException::~EngineException()
{
    delete InnerException;
}

[[nodiscard]] std::vector<std::string> EngineException::GetStackTrace() const
{
    std::vector<std::string> trace;
    trace.emplace_back(what());

    if (InnerException)
    {
        EngineException* innerException = InnerException;
        while (innerException)
        {
            trace.emplace_back(innerException->what());
            innerException = innerException->InnerException;
        }
    }

    return trace;
}

EngineException* EngineException::GetInnerException()
{
    return InnerException;
}

[[nodiscard]] std::string EngineException::GetStackTraceLocation() const
{
    std::ostringstream stream;
    stream << SourceFile << ":" << LineNumber << "->" << CallerFunction;
    return stream.str();
}