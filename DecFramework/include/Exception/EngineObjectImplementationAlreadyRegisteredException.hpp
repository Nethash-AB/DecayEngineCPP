#ifndef DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONALREADYREGISTEREDEXCEPTION_HPP
#define DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONALREADYREGISTEREDEXCEPTION_HPP

#include "Database/IDatabaseId.hpp"
#include "Exception/EngineException.hpp"
#include "Object/EngineObjectImplementation.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Exception
{
    class EngineObjectImplementationAlreadyRegisteredException : public EngineException
    {
        public:
            explicit EngineObjectImplementationAlreadyRegisteredException(const Object::EngineObjectType& type, const Object::engine_object_subtype_t& subType,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);
            explicit EngineObjectImplementationAlreadyRegisteredException(const Object::EngineObjectType& type, const Object::engine_object_subtype_t& subType,
                EngineException* innerException, int lineNumber, const std::string& callerFunction, const std::string& sourceFile);

            ~EngineObjectImplementationAlreadyRegisteredException() override;

            [[nodiscard]] const char* what() const override;
        private:
            const Object::EngineObjectType _type;
            const Object::engine_object_subtype_t _subType;
    };
}

#endif //DECAYENGINE_ENGINEOBJECTIMPLEMENTATIONALREADYREGISTEREDEXCEPTION_HPP
