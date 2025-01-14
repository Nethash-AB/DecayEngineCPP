#ifndef DECAYENGINE_STOPWATCH_HPP
#define DECAYENGINE_STOPWATCH_HPP

#include "Time.hpp"
#include <atomic>
#include <mutex>
#include <chrono>

namespace DecFramework::Time
{
    class StopWatch
    {
        public:
            explicit StopWatch();
            ~StopWatch();

            FractionSeconds GetElapsed();
            bool IsRunning();
            void Start();
            void Stop();
            void Reset();
            void Restart();
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
            std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period> _elapsedTime;
            std::atomic<bool> _running;
            mutable std::mutex _locker;
    };
}

#endif //DECAYENGINE_STOPWATCH_HPP
