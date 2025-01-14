#ifndef DECAYENGINE_CONSTANTCOUNTER_HPP
#define DECAYENGINE_CONSTANTCOUNTER_HPP

#define _CONST_COUNTER_GET_MACRO(_1, _2, _3, Name, ...) Name

#define _CONST_COUNTER_NEW_1(Name, StartValue, Step)\
using Name = EngineSdk::Util::ConstantCounter<__COUNTER__, StartValue, Step>

#define _CONST_COUNTER_NEW_2(Name, StartValue)\
_CONST_COUNTER_NEW_1(Name, StartValue, 1)

#define _CONST_COUNTER_NEW_3(Name)\
_CONST_COUNTER_NEW_2(Name, 0)

#define CONST_COUNTER_NEW(...) _CONST_COUNTER_GET_MACRO(__VA_ARGS__, _CONST_COUNTER_NEW_1, _CONST_COUNTER_NEW_2, _CONST_COUNTER_NEW_3)(__VA_ARGS__)

#define CONST_COUNTER_NEXT(Name) Name::Next<__COUNTER__>()
#define CONST_COUNTER_CURRENT(Name) Name::Current<__COUNTER__>()

namespace DecFramework::Util
{
    template <int StartN, int StartValue = 0, int Step = 1>
    class ConstantCounter
    {
        private:
            template <int N>
            struct Slot
            {
                friend constexpr int SlotValue(Slot<N>);
            };

            template <int N, int I>
            struct Writer
            {
                friend constexpr int SlotValue(Slot<N>)
                {
                    return I;
                };

                static constexpr int Value = I;
            };

            template <int N, int R = SlotValue(Slot<N>())>
            static constexpr int Reader(int, Slot<N>)
            {
                return R;
            }

            static_assert(sizeof(Writer<StartN, StartValue - Step>));

            template <int N>
            static constexpr int Reader(float, Slot<N>, int r = Reader(0, Slot<N - 1>()))
            {
                return r;
            }
        public:
            template <int N>
            static constexpr int Next(int r = Writer<N, Reader(0, Slot<N - 1>()) + 1>::Value)
            {
                return r;
            }

            template <int N>
            static constexpr int Current(int r = Writer<N, Reader(0, Slot<N - 1>())>::Value)
            {
                return r;
            }
    };
}

#endif //DECAYENGINE_CONSTANTCOUNTER_HPP
