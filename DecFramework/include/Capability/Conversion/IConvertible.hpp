#ifndef DECAYENGINE_ICONVERTIBLE_HPP
#define DECAYENGINE_ICONVERTIBLE_HPP

namespace DecFramework::Capability::Conversion
{
    template <typename TFrom>
    class IConvertibleFrom
    {
        public:
            virtual void ConvertFrom(const TFrom& rhs) const = 0;

            IConvertibleFrom(const TFrom& rhs)
            {
                ConvertFrom(rhs);
            }

            IConvertibleFrom& operator=(const TFrom& rhs)
            {
                return *this;
            }
        protected:
            virtual ~IConvertibleFrom() = default;
    };

    template <typename TTo>
    class IConvertibleTo
    {
        public:
            virtual TTo ConvertTo() const = 0;

            operator TTo() const
            {
                return ConvertTo();
            }
        protected:
            virtual ~IConvertibleTo() = default;
    };

    template <typename T>
    class IConvertible : public IConvertibleFrom<T>, public IConvertibleTo<T>
    {
        public:
            void ConvertFrom(const T& rhs) const override = 0;
            T ConvertTo() const override = 0;
        protected:
            virtual ~IConvertible() = default;
    };
}

#endif //DECAYENGINE_ICONVERTIBLE_HPP
