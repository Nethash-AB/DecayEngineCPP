#ifndef DECAYENGINE_DEPENDENCYNODENOTFOUNDEXCEPTION_HPP
#define DECAYENGINE_DEPENDENCYNODENOTFOUNDEXCEPTION_HPP

#include "Exception/EngineException.hpp"
#include "EngineSdk.hpp"

FWD_DATABASE_ID()

namespace DecFramework::Exception
{
    class DependencyNodeNotFoundException : public EngineException
    {
        public:
            explicit DependencyNodeNotFoundException(const Database::IDatabaseId* id,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);
            explicit DependencyNodeNotFoundException(const Database::IDatabaseId* id, EngineException* innerException,
                int lineNumber, const std::string& callerFunction, const std::string& sourceFile);

            ~DependencyNodeNotFoundException() override;

            [[nodiscard]] const char* what() const override;
        private:
            const Database::IDatabaseId* _id;
    };
}

#endif //DECAYENGINE_DEPENDENCYNODENOTFOUNDEXCEPTION_HPP
