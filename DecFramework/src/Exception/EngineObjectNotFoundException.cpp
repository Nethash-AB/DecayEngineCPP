#include "Exception/EngineObjectNotFoundException.hpp"
#include "Database/IDatabaseId.hpp"

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Object;

EngineObjectNotFoundException::EngineObjectNotFoundException(const IDatabaseId* id,
    int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _id(id), EngineException(nullptr, lineNumber, callerFunction, sourceFile)
{
}

EngineObjectNotFoundException::EngineObjectNotFoundException(const IDatabaseId* id, EngineException* innerException,
    int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _id(id), EngineException(innerException, lineNumber, callerFunction, sourceFile)
{
}

EngineObjectNotFoundException::~EngineObjectNotFoundException() = default;

[[nodiscard]] const char* EngineObjectNotFoundException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(EngineObjectNotFoundException) << ": No object found with ID (";
    stream << _id->ToString() << ")";
    stream << " | " << GetStackTraceLocation();

    return stream.str().c_str();
}