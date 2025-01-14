#ifndef DECAYENGINE_EVENTHANDLER_HPP
#define DECAYENGINE_EVENTHANDLER_HPP

#include "Delegate.hpp"
#include <functional>
#include <future>

namespace DecFramework::Event
{
    template <typename... Args>
    class EventHandler
    {
        public:
            explicit EventHandler() : _eventDelegates()
            {
            }

            ~EventHandler() = default;

            void Add(const Delegate<void, Args...>& delegate)
            {
                std::scoped_lock<std::mutex> lock(_locker);

                _eventDelegates.push_back(delegate);
            }

            bool Remove(const Delegate<void, Args...>& delegate)
            {
                std::scoped_lock<std::mutex> lock(_locker);

                auto it = std::find(_eventDelegates.begin(), _eventDelegates.end(), delegate);
                if (it != _eventDelegates.end())
                {
                    _eventDelegates.erase(it);
                    return true;
                }

                return false;
            }

            [[nodiscard]] bool Contains(const Delegate<void, Args...>& delegate) const
            {
                std::scoped_lock<std::mutex> lock(_locker);
                return std::find(_eventDelegates.begin(), _eventDelegates.end(), delegate) != _eventDelegates.end();
            }

            void Clear()
            {
                std::scoped_lock<std::mutex> lock(_locker);
                _eventDelegates.clear();
            }

            void Invoke(Args... params) const
            {
                EventDelegateCollection eventDelegatesCopy = GetEventDelegatesCopy();

                for (const auto& delegate : eventDelegatesCopy)
                {
                    delegate(std::forward<Args>(params)...);
                }
            }

            void operator()(Args... params) const
            {
                Invoke(std::forward<Args>(params)...);
            }

            void operator+=(const Delegate<void, Args...>& delegate)
            {
                return Add(delegate);
            }

            bool operator-=(const Delegate<void, Args...>& delegate)
            {
                return Remove(delegate);
            }
        private:
            typedef std::vector<Delegate<void, Args...>> EventDelegateCollection;
            EventDelegateCollection _eventDelegates;

            mutable std::mutex _locker;

            EventDelegateCollection GetEventDelegatesCopy() const
            {
                std::scoped_lock<std::mutex> lock(_locker);
                return _eventDelegates;
            }
    };
}

#endif //DECAYENGINE_EVENTHANDLER_HPP
