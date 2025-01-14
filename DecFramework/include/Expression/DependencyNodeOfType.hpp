#ifndef DECAYENGINE_DEPENDENCYNODEOFTYPE_HPP
#define DECAYENGINE_DEPENDENCYNODEOFTYPE_HPP

#include "Database/IDatabaseId.hpp"
#include "Graph/IDependencyNode.hpp"
#include "Expression/IExpression.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Expression
{
    class DependencyNodeOfType final : public IExpression<Graph::IDependencyNode>
    {
        public:
            explicit DependencyNodeOfType(Object::EngineObjectType type)
                : _type(type), _subType(0), _matchType(true), _matchSubType(false) {}

            explicit DependencyNodeOfType(Object::engine_object_subtype_t subType)
                : _type(Object::EngineObjectType::Invalid), _subType(subType), _matchType(false), _matchSubType(true) {}

            explicit DependencyNodeOfType(Object::EngineObjectType type, Object::engine_object_subtype_t subType)
                : _type(type), _subType(subType), _matchType(true), _matchSubType(true) {}

            ~DependencyNodeOfType() override = default;

            [[nodiscard]] bool Invoke(Graph::IDependencyNode* element) override
            {
                const Database::IDatabaseId* id = element->GetId();
                return (!_matchType || id->GetType() == _type) && (!_matchSubType || id->GetSubType() == _subType);
            }
        private:
            const Object::EngineObjectType _type;
            const Object::engine_object_subtype_t _subType;
            const bool _matchType;
            const bool _matchSubType;
    };
}

#endif //DECAYENGINE_DEPENDENCYNODEOFTYPE_HPP
