#ifndef DECAYENGINE_GAMEOBJECT_HPP
#define DECAYENGINE_GAMEOBJECT_HPP

#include "Object/EngineObjectImplementation.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Object
{
    class GameObjectImpl final : public Implementation::EngineObjectImplementation<Object::EngineObjectType::GameObject>::BaseType<
        Implementation::Feature::CreateCallbackFeature,
        Implementation::Feature::DeleteCallbackFeature,
        Implementation::Feature::CloneCallbackFeature>::type
    {
        public:
            explicit GameObjectImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj);
            ~GameObjectImpl() override;

            void OnCreate() override;
            void OnDelete() override;
            void OnClone(Object::IEngineObject* oldObject) override;
    };
}

#endif //DECAYENGINE_GAMEOBJECT_HPP
