#ifndef DECAYENGINE_ARGUMENTOUTOFRANGEEXCEPTION_HPP
#define DECAYENGINE_ARGUMENTOUTOFRANGEEXCEPTION_HPP

#include "Exception/ArgumentException.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Exception
{
    class ArgumentOutOfRangeException: public ArgumentException
    {
        public:
            explicit ArgumentOutOfRangeException(std::string message, int lineNumber, std::string callerFunction, std::string sourceFile);
            explicit ArgumentOutOfRangeException(std::string message, std::string paramName, int lineNumber, std::string callerFunction, std::string sourceFile);
            explicit ArgumentOutOfRangeException(std::string message, std::string paramName, EngineException* innerException,
                int lineNumber, std::string callerFunction, std::string sourceFile);

            ~ArgumentOutOfRangeException() override;

            [[nodiscard]] const char* what() const override;
    };
}

#endif //DECAYENGINE_ARGUMENTOUTOFRANGEEXCEPTION_HPP
