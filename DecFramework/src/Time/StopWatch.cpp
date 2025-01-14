#include "Time/StopWatch.hpp"

using namespace DecFramework::Time;

StopWatch::StopWatch() : _running(false), _startTime(), _elapsedTime()
{
}

StopWatch::~StopWatch() = default;

bool StopWatch::IsRunning()
{
    return _running;
}

FractionSeconds StopWatch::GetElapsed()
{
    std::scoped_lock<std::mutex> lock(_locker);

    if (!_running) return FractionSeconds(_elapsedTime);

    auto currentTimeStamp = std::chrono::high_resolution_clock::now();
    _elapsedTime = currentTimeStamp - _startTime;

    return FractionSeconds(_elapsedTime);
}

void StopWatch::Start()
{
    if (_running) return;

    std::scoped_lock<std::mutex> lock(_locker);

    _startTime = std::chrono::high_resolution_clock::now();
    _running = true;
}

void StopWatch::Stop()
{
    if (!_running) return;

    GetElapsed();
    _running = false;

    std::scoped_lock<std::mutex> lock(_locker);

    auto zero = std::chrono::time_point<std::chrono::high_resolution_clock>(std::chrono::nanoseconds{0});
    if (_elapsedTime < std::chrono::nanoseconds{0})
    {
        _elapsedTime = std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period>(0);
    }
}

void StopWatch::Reset()
{
    std::scoped_lock<std::mutex> lock(_locker);

    _elapsedTime = std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period>(0);
    _running = false;
    _startTime = std::chrono::time_point<std::chrono::high_resolution_clock>();
}

void StopWatch::Restart()
{
    std::scoped_lock<std::mutex> lock(_locker);

    _elapsedTime = std::chrono::duration<std::chrono::high_resolution_clock::rep, std::chrono::high_resolution_clock::period>(0);
    _startTime = std::chrono::high_resolution_clock::now();
    _running = true;
}