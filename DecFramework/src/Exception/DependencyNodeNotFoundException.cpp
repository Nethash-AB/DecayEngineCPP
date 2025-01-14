#include "Exception/DependencyNodeNotFoundException.hpp"
#include "Database/IDatabaseId.hpp"

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Object;

DependencyNodeNotFoundException::DependencyNodeNotFoundException(const IDatabaseId* id,
    int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _id(id), EngineException(nullptr, lineNumber, callerFunction, sourceFile)
{
}

DependencyNodeNotFoundException::DependencyNodeNotFoundException(const IDatabaseId* id, EngineException* innerException,
    int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _id(id), EngineException(innerException, lineNumber, callerFunction, sourceFile)
{
}

DependencyNodeNotFoundException::~DependencyNodeNotFoundException() = default;

[[nodiscard]] const char* DependencyNodeNotFoundException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(DependencyNodeNotFoundException) << ": No dependency node found with ID (";
    stream << _id->ToString() << ")";
    stream << " | " << GetStackTraceLocation();

    return stream.str().c_str();
}