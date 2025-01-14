//#include "Log/ConsoleLogger.hpp"
//
//using namespace DecFramework;
//using namespace DecFramework::Log;
//using namespace GameEngine::Log;
//
//ConsoleLogger::ConsoleLogger(IGlobalEnvironment* gEnv)
//    : UseDebugStream(false), AddSourceInfo(false), Logger(gEnv)
//{
//}
//
//ConsoleLogger::~ConsoleLogger() = default;
//
//void ConsoleLogger::AddMessage(const DecFramework::Log::LogMessage& message) const
//{
//    std::ostringstream outputStream;
//    //ToDo: Find a way to get a meaningful string from SubSystemId
//    outputStream << "[" << message.Severity << "]" << "(" << message.SubSystemId << ")" << ": " << message.Message;
//
//    if (AddSourceInfo)
//    {
//        outputStream << " | " << message.SourceFile << ":" << message.LineNumber << "->" << message.CallerFunction;
//    }
//
//    if (UseDebugStream)
//    {
//        std::clog << outputStream.str() << std::endl;
//    }
//    else
//    {
//        std::cout << outputStream.str() << std::endl;
//    }
//}