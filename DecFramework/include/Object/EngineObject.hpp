#ifndef DECAYENGINE_ENGINEOBJECT_HPP
#define DECAYENGINE_ENGINEOBJECT_HPP

#include "Capability/Equality/IEquatable.hpp"
#include "Object/EngineObjectImplementation.hpp"
#include "Object/EngineObjectType.hpp"
#include "EngineSdk.hpp"

#include "Database/IDatabaseId.hpp"

FWD_DATABASE_ID()
FWD_ENGINE_OBJECT()
FWD_OBJECT_DATABASE()
FWD_GRAPH_CONTROLLER()
FWD_GLOBAL_ENVIRONMENT()

namespace DecFramework::Object
{
    class IEngineObject : public virtual Capability::Equality::IEquatable<IEngineObject>
    {
        public:
            ~IEngineObject() override = default;

            [[nodiscard]] virtual const Database::IDatabaseId* GetId() const = 0;
            [[nodiscard]] virtual Implementation::IEngineObjectImplementation* GetImplementation() const = 0;
            [[nodiscard]] virtual Graph::IDependencyNode* GetNode() const = 0;
    };

    class EngineObject final : public IEngineObject
    {
        public:
            [[nodiscard]] const Database::IDatabaseId* GetId() const override;
            [[nodiscard]] Implementation::IEngineObjectImplementation* GetImplementation() const override;
            [[nodiscard]] Graph::IDependencyNode* GetNode() const override;

            [[nodiscard]] bool Equals(const IEngineObject* other) const override;

            explicit EngineObject(const IGlobalEnvironment* gEnv, const Database::IDatabaseId* id);
            ~EngineObject() override;

            void SetImplementation(Implementation::IEngineObjectImplementation* implementation);
        private:
            const IGlobalEnvironment* _gEnv;
            const Database::IDatabaseId* _id;
            Implementation::IEngineObjectImplementation* _implementation;
    };
}


#endif //DECAYENGINE_ENGINEOBJECT_HPP
