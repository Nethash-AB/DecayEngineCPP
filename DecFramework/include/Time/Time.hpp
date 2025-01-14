#ifndef DECAYENGINE_TIME_HPP
#define DECAYENGINE_TIME_HPP

#include <chrono>

namespace DecFramework::Time
{
    typedef std::chrono::duration<double, std::ratio<1>> FractionSeconds;
}

#endif //DECAYENGINE_TIME_HPP
