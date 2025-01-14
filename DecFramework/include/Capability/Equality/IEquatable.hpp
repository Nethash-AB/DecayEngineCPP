#ifndef DECAYENGINE_IEQUATABLE_HPP
#define DECAYENGINE_IEQUATABLE_HPP

#include "EngineSdk.hpp"

namespace DecFramework::Capability::Equality
{
    template <typename T>
    class IEquatable
    {
        public:
            [[nodiscard]] virtual bool Equals(const T* rhs) const = 0;
        protected:
            virtual ~IEquatable() = default;
    };

    template <typename T, std::enable_if_t<std::is_base_of_v<IEquatable<T>, T>>* = nullptr>
    inline bool operator==(const T& lhs, const T& rhs)
    {
        return lhs.Equals(&rhs);
    }

    template <typename T, std::enable_if_t<std::is_base_of_v<IEquatable<T>, T>>* = nullptr>
    inline bool operator!=(const T& lhs, const T& rhs)
    {
        return !lhs.Equals(&rhs);
    }
}

#endif //DECAYENGINE_IEQUATABLE_HPP
