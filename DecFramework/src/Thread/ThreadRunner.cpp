#include "Thread/ThreadRunner.hpp"

using namespace DecFramework::Thread;

ThreadRunner::~ThreadRunner() = default;

[[nodiscard]] bool ThreadRunner::Equals(const ThreadRunner* other) const
{
    return IsAlive() && other->IsAlive() && GetId() == other->GetId();
}