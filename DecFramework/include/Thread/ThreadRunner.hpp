#ifndef DECAYENGINE_THREADRUNNER_HPP
#define DECAYENGINE_THREADRUNNER_HPP

#include "Event/EventHandler.hpp"
#include "Time/Time.hpp"
#include <queue>
#include <future>

#define THREAD_ID(value) std::hash<std::thread::id>()(value::get_id())

namespace DecFramework
{
    class ITask;

    namespace Thread
    {
        class ThreadRunner : public Capability::Equality::IEquatable<ThreadRunner>
        {
            public:
                ~ThreadRunner() override;

                [[nodiscard]] virtual Event::EventHandler<Time::FractionSeconds> &OnUpdate() = 0;
                [[nodiscard]] virtual bool IsAlive() const = 0;
                [[nodiscard]] virtual bool IsExecutingInThisThread() const = 0;
                [[nodiscard]] virtual size_t GetId() const = 0;
                virtual void Run() = 0;
                virtual void Stop() = 0;
                virtual void Execute(ITask *task) = 0;

                [[nodiscard]] bool Equals(const ThreadRunner* other) const override;
        };
    }
}

#endif //DECAYENGINE_THREADRUNNER_HPP
