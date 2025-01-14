#ifndef DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONNOTFOUNDEXCEPTION_HPP
#define DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONNOTFOUNDEXCEPTION_HPP

#include "Database/IDatabaseId.hpp"
#include "Exception/EngineException.hpp"
#include "Object/EngineObjectImplementation.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Exception
{
    class EngineObjectImplementationNotFoundException : public EngineException
    {
        public:
            explicit EngineObjectImplementationNotFoundException(const Object::EngineObjectType& type, const Object::engine_object_subtype_t& subType,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);
            explicit EngineObjectImplementationNotFoundException(const Object::EngineObjectType& type, const Object::engine_object_subtype_t& subType,
                EngineException* innerException, int lineNumber, const std::string& callerFunction, const std::string& sourceFile);

            ~EngineObjectImplementationNotFoundException() override;

            [[nodiscard]] const char* what() const override;
        private:
            const Object::EngineObjectType _type;
            const Object::engine_object_subtype_t _subType;
    };
}

#endif //DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONNOTFOUNDEXCEPTION_HPP
