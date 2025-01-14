#ifndef DECAYENGINE_FUNCTION_HPP
#define DECAYENGINE_FUNCTION_HPP

namespace DecFramework
{
    template <typename F, F f>
    class Function;

    template <typename TClass, typename TRet, typename... TArgs, TRet(*f)(TArgs...)>
    class Function<TRet(TClass::*)(TArgs...), f>
    {
        private:
            struct is_member_f
            {
                using type = TClass;
                static constexpr bool value = true;
            };

            struct ret
            {
                using type = TRet;
            };

            template <typename... _TArgs>
            struct _args;

            struct args
            {
                using type = _args<TArgs...>;
            };

            struct func
            {
                using type = TRet(TClass::*)(TArgs...);
                static constexpr type value = f;
            };
        public:
            using type = Function;
            using is_member_f_t = typename is_member_f::type;
            using ret_t = typename ret::type;
            using args_t = typename args::type;
            using func_t = typename func::type;

            static constexpr bool is_member_f_v = is_member_f::value;
            static constexpr func_t func_v = func::value;
    };

    template <typename TRet, typename... TArgs, TRet(*f)(TArgs...)>
    class Function<TRet(*)(TArgs...), f>
    {
        private:
            struct is_member_f
            {
                static constexpr bool value = false;
            };

            struct ret
            {
                using type = TRet;
            };

            template <typename... _TArgs>
            struct _args;

            struct args
            {
                using type = _args<TArgs...>;
            };

            struct func
            {
                using type = TRet(*)(TArgs...);
                static constexpr type value = f;
            };
        public:
            using type = Function;
            using ret_t = typename ret::type;
            using args_t = typename args::type;
            using func_t = typename func::type;

            static constexpr bool is_member_f_v = is_member_f::value;
            static constexpr func_t func_v = func::value;
    };
}

#endif //DECAYENGINE_FUNCTION_HPP