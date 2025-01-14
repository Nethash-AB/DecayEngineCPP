#ifndef DECAYENGINE_ENGINEOBJECTIMPLEMENTATION_HPP
#define DECAYENGINE_ENGINEOBJECTIMPLEMENTATION_HPP

#include "Object/EngineObjectType.hpp"
#include "Function.hpp"
#include "EngineSdk.hpp"
#include <functional>

FWD_OBJECT_FACTORY()
FWD_ENGINE_OBJECT()

namespace DecFramework::Object::Implementation
{
    namespace Feature
    {
        struct ImplementationFeature
        {
            using type = ImplementationFeature;
        };

        template <typename... TFeatures>
        class FeatureSet
        {
            private:
                template <bool>
                struct FeatureBaseType;

                template<> struct FeatureBaseType<true> : public virtual TFeatures... {};
                template<> struct FeatureBaseType<false> {};
            public:
                using type = FeatureSet;

                static constexpr bool IsValid = std::conjunction_v<std::is_base_of<ImplementationFeature, TFeatures>...>;
                using base_type_t = FeatureBaseType<IsValid>;

                template <typename TFeature>
                using HasFeature = typename std::conditional_t<std::disjunction_v<std::is_same<TFeatures, TFeature>...>, std::true_type, std::false_type>::type;
        };

        struct CreateCallbackFeature : public ImplementationFeature
        {
            using type = CreateCallbackFeature;

            virtual ~CreateCallbackFeature() = default;
            virtual void OnCreate() = 0;

            void operator()()
            {
                OnCreate();
            }
        };

        struct DeleteCallbackFeature : public ImplementationFeature
        {
            using type = DeleteCallbackFeature;

            virtual ~DeleteCallbackFeature() = default;
            virtual void OnDelete() = 0;

            void operator()()
            {
                OnDelete();
            }
        };

        struct CloneCallbackFeature : public ImplementationFeature
        {
            using type = CloneCallbackFeature;

            virtual ~CloneCallbackFeature() = default;
            virtual void OnClone(Object::IEngineObject* oldObject) = 0;

            void operator()(Object::IEngineObject* oldObject)
            {
                OnClone(oldObject);
            }
        };
    }

    class IEngineObjectImplementation
    {
        private:
            template <typename TFeature, typename TRet, typename... TArgs>
            static constexpr std::function<TRet(TArgs...)> GetFeatureFunc(TRet(TFeature::*f)(TArgs...), IEngineObjectImplementation* instance = nullptr)
            {
                TFeature* feature = dynamic_cast<TFeature*>(instance);
                if (!feature)
                {
                    return std::function<TRet(TArgs...)>();
                }

                return [f, feature](TArgs... args) {
                    if constexpr (!std::is_void_v<TRet>)
                    {
                        return (feature->*f)(args...);
                    }
                    (feature->*f)(args...);
                };
            }

            template <typename F>
            struct IsValidFeatureFunc
            {
                using type = IsValidFeatureFunc;

                template <typename _F>
                static constexpr bool IsValid(_F f)
                {
                    return false;
                }

                template<> static constexpr bool IsValid<F>(F f)
                {
                    return true;
                };
            };
        public:
            virtual ~IEngineObjectImplementation() = default;

            template<typename TFeature, std::enable_if_t<std::is_base_of_v<Feature::ImplementationFeature, TFeature>>* = nullptr>
            [[nodiscard]] bool HasFeature()
            {
                return (dynamic_cast<TFeature*>(this) != nullptr);
            }

            template <typename TFeature, typename... TArgs,
                typename TFunc = decltype(GetFeatureFunc(&TFeature::operator())),
                typename TRet = typename TFunc::result_type,
                std::enable_if_t<IsValidFeatureFunc<TRet(TFeature::*)(TArgs...)>::IsValid(&TFeature::operator())>* = nullptr,
                std::enable_if_t<std::is_base_of_v<Feature::ImplementationFeature, TFeature>>* = nullptr>
            TRet TryInvokeFeature(TArgs... args)
            {
                if (!std::is_void_v<TRet>)
                {
                    return GetFeatureFunc(&TFeature::operator(), this)(args...);
                }
                else
                {
                    GetFeatureFunc(&TFeature::operator(), this)(args...);
                }
            }
        private:


            friend class DecFramework::Object::ObjectFactory;
    };

    template <typename TImpl>
    static constexpr bool IsValidImplementation =
        std::is_base_of<IEngineObjectImplementation, TImpl>::value &&
        std::is_constructible<TImpl, const IGlobalEnvironment*, Object::IEngineObject*>::value;

    class CreateFunction
    {
        private:
            template <typename TImpl = void>
            static IEngineObjectImplementation* Create(const IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
            {
                return new TImpl(gEnv, obj);
            }
        public:
            using type = CreateFunction;

            template <typename TImpl, std::enable_if_t<IsValidImplementation<TImpl>>* = nullptr>
            static implementation_create_func_t Get()
            {
                return &Create<TImpl>;
            }
    };

    namespace _
    {
        template <Object::EngineObjectType TObjectType, typename... TFeatures>
        class EngineObjectImplementationTyped : public IEngineObjectImplementation, public Feature::FeatureSet<TFeatures...>::base_type_t
        {
            public:
                using type = EngineObjectImplementationTyped;
                using feature_set = Feature::FeatureSet<Feature::CreateCallbackFeature, TFeatures...>;

                struct BaseType
                {
                    using base_implementation_t = EngineObjectImplementationTyped;
                    static constexpr Object::EngineObjectType Type = TObjectType;
                    static constexpr Object::engine_object_subtype_t SubType = 0;
                };

                ~EngineObjectImplementationTyped() override = default;
            protected:
                const IGlobalEnvironment* GEnv;
                Object::IEngineObject* Object;

                explicit EngineObjectImplementationTyped(const IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
                    : GEnv(gEnv), Object(obj)
                {
                }
        };

        template <Object::EngineObjectType TObjectType, Object::engine_object_subtype_t TObjectSubType, typename... TFeatures>
        struct EngineObjectImplementationSubTyped : public EngineObjectImplementationTyped<TObjectType, TFeatures...>
        {
            public:
                using type = EngineObjectImplementationSubTyped;

                struct BaseType
                {
                    using base_implementation_t = EngineObjectImplementationSubTyped;
                    static constexpr Object::EngineObjectType Type = TObjectType;
                    static constexpr Object::engine_object_subtype_t SubType = TObjectSubType;
                };

                ~EngineObjectImplementationSubTyped() override = default;
            protected:
                explicit EngineObjectImplementationSubTyped(const IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
                    : EngineObjectImplementationTyped(gEnv, obj)
                {
                }
        };
    }

    template <Object::EngineObjectType TObjectType, bool = Object::IsSubtypedType(TObjectType)>
    struct EngineObjectImplementation;

    template <Object::EngineObjectType TObjectType>
    struct EngineObjectImplementation<TObjectType, false>
    {
        template <typename... TFeatures>
        struct BaseType
        {
            using type = std::enable_if_t<Feature::FeatureSet<TFeatures...>::IsValid, _::EngineObjectImplementationTyped<TObjectType, TFeatures...>>;
        };
    };

    template <Object::EngineObjectType TObjectType>
    struct EngineObjectImplementation<TObjectType, true>
    {
        template <Object::engine_object_subtype_t TObjectSubType, typename... TFeatures>
        struct BaseType
        {
            using type =
                std::enable_if_t<Feature::FeatureSet<TFeatures...>::IsValid, _::EngineObjectImplementationSubTyped<TObjectType, TObjectSubType, TFeatures...>>;
        };
    };
}

#endif //DECAYENGINE_ENGINEOBJECTIMPLEMENTATION_HPP
