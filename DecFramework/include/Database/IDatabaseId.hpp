#ifndef DECAYENGINE_IDATABASEID_HPP
#define DECAYENGINE_IDATABASEID_HPP

#include "Capability/Equality/IEquatable.hpp"
#include "EngineSdk.hpp"
#include <string>

FWD_DATABASE_ID()

namespace DecFramework::Database
{
    class IDatabaseId : public Capability::Equality::IEquatable<const IDatabaseId>
    {
        public:
            ~IDatabaseId() override = default;

            [[nodiscard]] virtual Object::EngineObjectType GetType() const = 0;
            [[nodiscard]] virtual Object::engine_object_subtype_t GetSubType() const = 0;
            [[nodiscard]] virtual Object::engine_object_instance_t GetInstance() const = 0;
            [[nodiscard]] virtual bool IsRuntimeInstance() const = 0;
            [[nodiscard]] virtual bool IsInstanceOf(const IDatabaseId& rhs) const = 0;
            [[nodiscard]] virtual std::string ToString() const = 0;

            [[nodiscard]] bool Equals(const IDatabaseId* other) const override = 0;
    };
}

#endif //DECAYENGINE_IDATABASEID_HPP
