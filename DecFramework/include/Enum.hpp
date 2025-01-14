#ifndef DECAYENGINE_ENUM_HPP
#define DECAYENGINE_ENUM_HPP

#include <bitset>

namespace DecFramework
{
    template <typename TEnum>
    class FlagsEnum
    {
        static_assert(std::is_enum<TEnum>::value);
        public:
            explicit FlagsEnum() = default;

            FlagsEnum(const TEnum& rhs)
            {
                _bits.set(static_cast<underlying_type_t>(rhs));
            }

            FlagsEnum& operator=(const TEnum& rhs)
            {
                _bits.set(static_cast<underlying_type_t>(rhs))
            }

            FlagsEnum& operator|=(const TEnum& rhs)
            {
                _bits.set(static_cast<underlying_type_t>(rhs));
                return *this;
            }

            FlagsEnum& operator|=(const FlagsEnum& rhs)
            {
                _bits |= rhs._bits;
                return *this;
            }

            FlagsEnum& operator&=(const TEnum& rhs)
            {
                bool res = _bits.test(static_cast<underlying_type_t>(rhs));
                _bits.reset();
                _bits.set(static_cast<underlying_type_t>(rhs), res);
                return *this;
            }

            FlagsEnum& operator&=(const FlagsEnum& rhs)
            {
                _bits &= rhs._bits;
                return *this;
            }

            FlagsEnum operator|(const TEnum& rhs)
            {
                FlagsEnum result(*this);
                result |= rhs;

                return result;
            }

            FlagsEnum operator|(const FlagsEnum& rhs)
            {
                FlagsEnum result(*this);
                result._bits |= rhs._bits;

                return result;
            }

            FlagsEnum operator&(const TEnum& rhs)
            {
                FlagsEnum result(*this);
                result &= rhs;

                return result;
            }

            FlagsEnum operator&(const FlagsEnum& rhs)
            {
                FlagsEnum result(*this);
                result._bits &= rhs._bits;

                return result;
            }

            FlagsEnum operator~()
            {
                FlagsEnum result(*this);
                result._bits.flip();

                return result;
            }

            explicit operator bool() const
            {
                return _bits.any();
            }

            [[nodiscard]] std::size_t size() const
            {
                return _bits.size();
            }

            [[nodiscard]] std::size_t count() const
            {
                return _bits.count();
            }

            FlagsEnum& set()
            {
                _bits.set();
                return *this;
            }

            FlagsEnum& reset()
            {
                _bits.reset();
                return *this;
            }

            FlagsEnum& flip()
            {
                _bits.flip();
                return *this;
            }

            FlagsEnum& set(const TEnum& rhs, bool value = true)
            {
                _bits.set(static_cast<underlying_type_t>(rhs), value);
                return *this;
            }

            FlagsEnum& reset(const TEnum& rhs)
            {
                _bits.reset(static_cast<underlying_type_t>(rhs));
                return *this;
            }

            FlagsEnum& flip(const TEnum& rhs)
            {
                _bits.flip(static_cast<underlying_type_t>(rhs));
                return *this;
            }

            bool operator[](const TEnum& rhs)
            {
                return _bits[static_cast<underlying_type_t>(rhs)];
            }

            friend std::ostream& operator<<(std::ostream& lhs, const FlagsEnum& rhs)
            {
                return lhs << rhs._bits;
            }

            bool operator==(const FlagsEnum<TEnum> &other) const
            {
                return _bits == other._bits;
            }
        private:
            using underlying_type_t = typename std::underlying_type_t<TEnum>;

            std::bitset<static_cast<underlying_type_t>(TEnum::_)> _bits;
    };

    template <typename TEnum, typename = void>
    struct IsFlagsEnum : std::false_type
    {
    };

    template <typename TEnum>
    struct IsFlagsEnum<TEnum, decltype(static_cast<void>(TEnum::_))> : std::is_enum<TEnum>
    {
    };

    template<typename TEnum>
    inline constexpr std::enable_if_t<IsFlagsEnum<TEnum>::value, FlagsEnum<TEnum>> operator|(const TEnum& lhs, const TEnum& rhs)
    {
        FlagsEnum<TEnum> result;
        result |= lhs;
        result |= rhs;

        return result;
    }
}

#endif //DECAYENGINE_ENUM_HPP
