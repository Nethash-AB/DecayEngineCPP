#ifndef DECAYENGINE_ARGUMENTEXCEPTION_HPP
#define DECAYENGINE_ARGUMENTEXCEPTION_HPP

#include "Exception/EngineException.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Exception
{
    class ArgumentException : public EngineException
    {
        public:
            explicit ArgumentException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile);
            explicit ArgumentException(std::string message, std::string paramName, int lineNumber, std::string callerFunction, std::string sourceFile);
            explicit ArgumentException(std::string message, std::string paramName, EngineException* innerException,
                int lineNumber, std::string callerFunction, std::string sourceFile);

            ~ArgumentException() override;

            [[nodiscard]] const char* what() const override;
        protected:
            std::string ParamName;
            std::string Message;
    };
}

#endif //DECAYENGINE_ARGUMENTEXCEPTION_HPP
