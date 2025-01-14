#ifndef DECAYENGINE_FORMATEXCEPTION_HPP
#define DECAYENGINE_FORMATEXCEPTION_HPP

#include "Exception/EngineException.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Exception
{
    class FormatException: public EngineException
    {
        public:
            explicit FormatException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile);
            explicit FormatException(std::string message, EngineException* innerException, int lineNumber, std::string callerFunction, std::string sourceFile);

            ~FormatException() override = default;

            [[nodiscard]] const char* what() const override;
        private:
            std::string _message;
    };
}

#endif //DECAYENGINE_FORMATEXCEPTION_HPP
