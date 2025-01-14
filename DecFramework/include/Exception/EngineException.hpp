#ifndef DECAYENGINE_ENGINEEXCEPTION_HPP
#define DECAYENGINE_ENGINEEXCEPTION_HPP

#include <exception>
#include <string>
#include <vector>

namespace DecFramework::Exception
{
    class EngineException : public std::exception
    {
        public:
            ~EngineException() override;

            [[nodiscard]] std::vector<std::string> GetStackTrace() const;
            EngineException* GetInnerException();
        protected:
            EngineException* InnerException;
            int LineNumber;
            std::string CallerFunction;
            std::string SourceFile;

            explicit EngineException(EngineException* innerException, int lineNumber, std::string callerFunction, std::string sourceFile);

            [[nodiscard]] std::string GetStackTraceLocation() const;
    };
}

#endif //DECAYENGINE_ENGINEEXCEPTION_HPP