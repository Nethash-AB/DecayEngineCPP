#ifndef DECAYENGINE_SCENEOBJECT_HPP
#define DECAYENGINE_SCENEOBJECT_HPP

#include "Object/EngineObjectImplementation.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Object
{
    class SceneImpl final : public Implementation::EngineObjectImplementation<Object::EngineObjectType::Scene>::BaseType<
        Implementation::Feature::CreateCallbackFeature,
        Implementation::Feature::DeleteCallbackFeature,
        Implementation::Feature::CloneCallbackFeature>::type
    {
        public:
            explicit SceneImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj);
            ~SceneImpl() override;

            void OnCreate() override;
            void OnDelete() override;
            void OnClone(Object::IEngineObject* oldObject) override;
    };
}

#endif //DECAYENGINE_SCENEOBJECT_HPP
