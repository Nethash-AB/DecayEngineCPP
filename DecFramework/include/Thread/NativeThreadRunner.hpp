#ifndef DECAYENGINE_NATIVETHREADRUNNER_HPP
#define DECAYENGINE_NATIVETHREADRUNNER_HPP

#include "Thread/ThreadRunner.hpp"
#include "Time/StopWatch.hpp"

namespace DecFramework::Thread
{
    class NativeThreadRunner : public ThreadRunner
    {
        public:
            explicit NativeThreadRunner(double ticksPerSecond);
            ~NativeThreadRunner() override;

            [[nodiscard]] Event::EventHandler<Time::FractionSeconds> &OnUpdate() override;
            [[nodiscard]] bool IsAlive() const override;
            [[nodiscard]] bool IsExecutingInThisThread() const override;
            [[nodiscard]] size_t GetId() const override;
            void Run() override;
            void Stop() override;
            void Execute(ITask *task) override;
        private:
            std::atomic<bool> _alive;
            std::atomic<bool> _running;

            Event::EventHandler<Time::FractionSeconds> _onUpdateHandler;
            std::queue<std::reference_wrapper<ITask>> _taskQueue;
            mutable std::mutex _locker;

            Time::FractionSeconds _timeBetweenTicks;
            Time::StopWatch _threadTimer;
            Time::StopWatch _updateTimer;

            std::thread _thread;

            void Loop();
            bool IsTaskQueueEmpty();
            void RunTasks();
    };
}

#endif //DECAYENGINE_NATIVETHREADRUNNER_HPP
