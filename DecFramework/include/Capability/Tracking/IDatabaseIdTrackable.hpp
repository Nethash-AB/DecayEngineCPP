#ifndef DECAYENGINE_IDATABASEIDTRACKABLE_HPP
#define DECAYENGINE_IDATABASEIDTRACKABLE_HPP

#include "Capability/Equality/IEquatable.hpp"
#include "Database/IDatabaseId.hpp"
#include "Tracking/IDecayObject.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Capability::Tracking
{
    class IDatabaseIdTrackable
        : public virtual DecFramework::Tracking::IDecayObject,
        public virtual Capability::Equality::IEquatable<IDatabaseIdTrackable>,
        public virtual Capability::Equality::IEquatable<Database::IDatabaseId>
    {
        public:
            [[nodiscard]] virtual const Database::IDatabaseId* GetId() const = 0;

            [[nodiscard]] bool Equals(const IDatabaseIdTrackable* rhs) const override
            {
                return GetId()->Equals(rhs->GetId());
            }

            [[nodiscard]] bool Equals(const Database::IDatabaseId* rhs) const override
            {
                return GetId()->Equals(rhs);
            }
        protected:
            ~IDatabaseIdTrackable() override = default;
    };
}

#endif //DECAYENGINE_IDATABASEIDTRACKABLE_HPP
