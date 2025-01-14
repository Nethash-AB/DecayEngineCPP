#ifndef DECAYENGINE_STRING_HPP
#define DECAYENGINE_STRING_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>

namespace DecFramework::Util::String
{
    template<typename T>
    inline std::string ToHexString(T x)
    {
        std::ostringstream stream;
        stream << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << x;
        return stream.str();
    }

    inline std::string TrimLeft(const std::string& x)
    {
        return x.substr(x.find_first_not_of(" \n\r\t"));
    }

    inline std::string TrimRight(const std::string& x)
    {
        std::string s = x;
        s.erase(s.find_last_not_of(" \n\r\t") + 1);
        return s;
    }

    inline std::string Trim(const std::string& x)
    {
        return TrimRight(TrimLeft(x));
    }

    inline std::vector<std::string> Split(const std::string& x, const char& deliminter)
    {
        std::vector<std::string> results;
        std::istringstream stream(x);

        std::string s;
        while(std::getline(stream, s, deliminter))
        {
            results.push_back(s);
        }

        return results;
    }
}

#endif //DECAYENGINE_STRING_HPP
