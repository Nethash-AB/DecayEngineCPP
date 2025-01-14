#ifndef DECAYENGINE_IDEPENDENCYNODE_HPP
#define DECAYENGINE_IDEPENDENCYNODE_HPP

#include "Capability/Tracking/IDatabaseIdTrackable.hpp"
#include "EngineSdk.hpp"
#include <vector>

namespace DecFramework::Graph
{
    class IDependencyNode : public Capability::Tracking::IDatabaseIdTrackable
    {
        public:
            [[nodiscard]] const Database::IDatabaseId* GetId() const override = 0;
            [[nodiscard]] virtual bool IsValidReference() const = 0;

            [[nodiscard]] virtual IDependencyNode* GetRoot() const = 0;
            [[nodiscard]] virtual IDependencyNode* GetParent() const = 0;
            virtual void SetParent(IDependencyNode* newParent) = 0;

            virtual bool AddChild(IDependencyNode* child) = 0;
            [[nodiscard]] virtual std::vector<IDependencyNode*> GetChildren(const Expression::IExpression<IDependencyNode*>* predicate) const = 0;
            [[nodiscard]] virtual std::vector<IDependencyNode*> GetChildren() const = 0;
            virtual bool RemoveChild(IDependencyNode* child) = 0;
        protected:
            ~IDependencyNode() override = default;
    };
}

#endif //DECAYENGINE_IDEPENDENCYNODE_HPP
