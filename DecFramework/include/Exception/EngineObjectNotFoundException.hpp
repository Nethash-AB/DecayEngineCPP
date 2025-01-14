#ifndef DECAYENGINE_ENGINEOBJECTNOTFOUNDEXCEPTION_HPP
#define DECAYENGINE_ENGINEOBJECTNOTFOUNDEXCEPTION_HPP

#include "Exception/EngineException.hpp"
#include "EngineSdk.hpp"

FWD_DATABASE_ID()

namespace DecFramework::Exception
{
    class EngineObjectNotFoundException : public EngineException
    {
        public:
            explicit EngineObjectNotFoundException(const Database::IDatabaseId* id,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);
            explicit EngineObjectNotFoundException(const Database::IDatabaseId* id, EngineException* innerException,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);

            ~EngineObjectNotFoundException() override;

            [[nodiscard]] const char* what() const override;
        private:
            const Database::IDatabaseId* _id;
    };
}

#endif //DECAYENGINE_ENGINEOBJECTNOTFOUNDEXCEPTION_HPP
