#ifndef DECAYENGINE_TASK_HPP
#define DECAYENGINE_TASK_HPP

#include "ITask.hpp"
#include "Delegate.hpp"
#include <future>

namespace DecFramework
{
    template <typename Ret = void>
    class Task : public ITask
    {
        public:
            explicit Task(const Delegate<Ret>& delegate)
                : _task(std::bind(&Delegate<Ret>::Invoke, delegate)), _future(_task.get_future()), _complete(false)
            {
            }

            explicit Task(const std::function<Ret(void)>& function)
                : _task(function), _future(_task.get_future()), _complete(false)
            {
            }

            [[nodiscard]] bool IsComplete() const override
            {
                return _complete;
            }

            void Run() override
            {
                if (_complete) return;

                _task();
                _complete = true;
            }

            void Wait() override
            {
                if (_complete) return;

                _future.wait();
            }

            Ret Result() const
            {
                return _future.get();
            }

            void Reset() override
            {
                if (!_complete) return;

                _task.reset();
                _complete = false;
            }

            void operator()() const
            {
                Run();
            }
        private:
            std::packaged_task<Ret(void)> _task;
            std::future<Ret> _future;
            std::atomic<bool> _complete;
    };
}

#endif //DECAYENGINE_TASK_HPP
