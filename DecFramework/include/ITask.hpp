#ifndef DECAYENGINE_ITASK_HPP
#define DECAYENGINE_ITASK_HPP

namespace DecFramework
{
    class ITask
    {
        public:
            virtual ~ITask() = default;

            [[nodiscard]] virtual bool IsComplete() const = 0;
            virtual void Run() = 0;
            virtual void Wait() = 0;
            virtual void Reset() = 0;
    };
}

#endif //DECAYENGINE_ITASK_HPP
