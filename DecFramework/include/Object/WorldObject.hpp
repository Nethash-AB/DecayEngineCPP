#ifndef DECAYENGINE_WORLDOBJECT_HPP
#define DECAYENGINE_WORLDOBJECT_HPP

#include "Object/EngineObjectImplementation.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Object
{
    class WorldImpl final : public Implementation::EngineObjectImplementation<Object::EngineObjectType::World>::BaseType<
        Implementation::Feature::CreateCallbackFeature,
        Implementation::Feature::DeleteCallbackFeature,
        Implementation::Feature::CloneCallbackFeature>::type
    {
        public:
            explicit WorldImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj);
            ~WorldImpl() override;

            void OnCreate() override;
            void OnDelete() override;
            void OnClone(Object::IEngineObject* oldObject) override;
    };
}

#endif //DECAYENGINE_WORLDOBJECT_HPP
