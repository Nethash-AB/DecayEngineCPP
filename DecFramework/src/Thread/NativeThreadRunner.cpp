#include "Thread/NativeThreadRunner.hpp"
#include "ITask.hpp"

using namespace DecFramework;
using namespace DecFramework::Thread;

NativeThreadRunner::NativeThreadRunner(double ticksPerSecond)
    : _alive(false), _running(false), _taskQueue(), _onUpdateHandler(),
    _timeBetweenTicks(Time::FractionSeconds(1 / ticksPerSecond)), _threadTimer(),
    _updateTimer(), _thread()
{
}

NativeThreadRunner::~NativeThreadRunner()
{
    if (this->IsAlive())
    {
        _running = false;
        _thread.join();
    }
}

[[nodiscard]] Event::EventHandler<Time::FractionSeconds>& NativeThreadRunner::OnUpdate()
{
    return _onUpdateHandler;
}

[[nodiscard]] bool NativeThreadRunner::IsAlive() const
{
    return _alive;
}

[[nodiscard]] bool NativeThreadRunner::IsExecutingInThisThread() const
{
    if (!IsAlive())
        return false;

    return std::this_thread::get_id() == _thread.get_id();
}

[[nodiscard]] size_t NativeThreadRunner::GetId() const
{
    if (_alive)
    {
        return std::hash<std::thread::id>()(_thread.get_id());
    }

    return -1;
}

void NativeThreadRunner::Run()
{
    if (IsAlive())
        return;

    _running = true;
    _thread = std::thread(std::bind(&NativeThreadRunner::Loop, this));
}

void NativeThreadRunner::Stop()
{
    if (!IsAlive())
        return;

    _running = false;
    _thread.join();
}

void NativeThreadRunner::Execute(ITask *task)
{
    if (IsExecutingInThisThread())
    {
        task->Run();
    }
    else
    {
        std::scoped_lock<std::mutex> lock(_locker);
        _taskQueue.push(*task);
    }
}

void NativeThreadRunner::Loop()
{
    _alive = true;

    _threadTimer.Start();
    _updateTimer.Start();
    while (_running)
    {
        RunTasks();

        Time::FractionSeconds deltaTime = _updateTimer.GetElapsed();
        _updateTimer.Restart();

        _onUpdateHandler.Invoke(deltaTime);

        while (_threadTimer.GetElapsed() < _timeBetweenTicks)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds{1});
        }
        _threadTimer.Restart();
    }
    _threadTimer.Stop();
    _updateTimer.Stop();

    RunTasks();

    _alive = false;
}

bool NativeThreadRunner::IsTaskQueueEmpty()
{
    std::scoped_lock<std::mutex> lock(_locker);
    return _taskQueue.empty();
}

void NativeThreadRunner::RunTasks()
{
    while (!IsTaskQueueEmpty())
    {
        if (!_locker.try_lock())
            return;

        ITask *task = &_taskQueue.front().get();
        _taskQueue.pop();

        _locker.unlock();
        task->Run();
    }
}