#include "Exception/EngineObjectImplementationNotFoundException.hpp"

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Object;

EngineObjectImplementationNotFoundException::EngineObjectImplementationNotFoundException(const EngineObjectType& type, const engine_object_subtype_t& subType,
    int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _type(type), _subType(subType), EngineException(nullptr, lineNumber, callerFunction, sourceFile)
{
}

EngineObjectImplementationNotFoundException::EngineObjectImplementationNotFoundException(const EngineObjectType& type, const engine_object_subtype_t& subType,
    EngineException* innerException, int lineNumber, const std::string& callerFunction, const std::string& sourceFile)
    : _type(type), _subType(subType), EngineException(innerException, lineNumber, callerFunction, sourceFile)
{
}

EngineObjectImplementationNotFoundException::~EngineObjectImplementationNotFoundException() = default;

[[nodiscard]] const char* EngineObjectImplementationNotFoundException::what() const
{
    std::ostringstream stream;
    stream << NAMEOF(ObjectFactoryAlreadyRegisteredException) << ": EngineObject implementation of type ";
    stream << "(" << _type << ") ";
    if (IsSubtypedType(_type))
    {
        stream << "and subtype ";
        stream << "(" << std::to_string(_subType) << ") ";
    }
    stream << "not found.";
    stream << " | " << GetStackTraceLocation();

    return stream.str().c_str();
}