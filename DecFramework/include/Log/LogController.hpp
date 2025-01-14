#ifndef DECAYENGINE_LOGCONTROLLER_HPP
#define DECAYENGINE_LOGCONTROLLER_HPP

#include "Log/Logger.hpp"
#include "EngineSdk.hpp"
#include <unordered_map>
#include <vector>
#include <algorithm>

FWD_LOG_CONTROLLER()
FWD_GLOBAL_ENVIRONMENT()

namespace DecFramework::Log
{
    class LogController
    {
        public:
            template <class TLogger, std::enable_if_t<std::is_base_of<Logger, TLogger>::value>* = nullptr>
            TLogger* CreateLogger()
            {
                TLogger* logger = new TLogger(_gEnv);
                _loggers.push_back(logger);
                return logger;
            }

            template <class TLogger, std::enable_if_t<std::is_base_of<Logger, TLogger>::value>* = nullptr>
            bool DeleteLogger(TLogger* logger)
            {
                auto it = _loggers.find(logger);
                if (it != _loggers.end())
                {
                    _loggers.erase(it);
                    delete logger;
                    return true;
                }
                return false;
            }

            void Print(const LogMessage& message);
        private:
            IGlobalEnvironment* _gEnv;
            std::vector<Logger*> _loggers;

            explicit LogController(IGlobalEnvironment* gEnv);
            ~LogController();

            friend class DecFramework::IGlobalEnvironment;
    };
}

#endif //DECAYENGINE_LOGCONTROLLER_HPP
