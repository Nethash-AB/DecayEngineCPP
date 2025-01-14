#ifndef DECAYENGINE_DEPENDENCYNODE_HPP
#define DECAYENGINE_DEPENDENCYNODE_HPP

#include <Graph/IDependencyNode.hpp>

namespace DecCore::Graph
{
    class DependencyNode final : public DecFramework::Graph::IDependencyNode
    {
        public:
            using predicate_expression_t = DecFramework::Expression::IExpression<IDependencyNode*>;

            explicit DependencyNode(const DecFramework::Database::IDatabaseId* id);

            [[nodiscard]] const DecFramework::Database::IDatabaseId* GetId() const override;
            [[nodiscard]] bool IsValidReference() const override;

            [[nodiscard]] IDependencyNode* GetRoot() const override;
            [[nodiscard]] IDependencyNode* GetParent() const override;
            void SetParent(IDependencyNode* newParent) override;

            bool AddChild(IDependencyNode* child) override;
            [[nodiscard]] std::vector<IDependencyNode*> GetChildren(const predicate_expression_t* predicate) const override;
            [[nodiscard]] std::vector<IDependencyNode*> GetChildren() const override;
            bool RemoveChild(IDependencyNode* child) override;
        private:
            IDependencyNode* _parent;
            std::vector<IDependencyNode*> _children;
            const DecFramework::Database::IDatabaseId* _id;
        protected:
            ~DependencyNode() override;
    };
}

#endif //DECAYENGINE_IDEPENDENCYNODE_HPP
