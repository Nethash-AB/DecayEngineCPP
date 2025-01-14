#include "Graph/DependencyNode.hpp"
#include <Expression/IExpression.hpp>
#include <IGlobalEnvironment.hpp>

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Expression;
using namespace DecFramework::Graph;
using namespace DecFramework::Object;

using namespace DecCore;
using namespace DecCore::Graph;

DependencyNode::DependencyNode(const IDatabaseId* id)
    : _parent(), _children(), _id(id)
{
}

DependencyNode::~DependencyNode()
{
    if (_parent)
    {
        _parent->RemoveChild(this);
        _parent = nullptr;
    }

    for (auto* it : _children)
    {
        GetGEnv()->GetGraphController()->DeleteNode(it);
    }
}

[[nodiscard]] const Database::IDatabaseId* DependencyNode::GetId() const
{
    return _id;
}

[[nodiscard]] bool DependencyNode::IsValidReference() const
{
    return GetGEnv()->GetObjectDatabase()->IsValidReference(GetId());
}

[[nodiscard]] IDependencyNode* DependencyNode::GetRoot() const
{
    if (!_parent)
    {
        return (IDependencyNode*) this;
    }

    IDependencyNode* parent = _parent;
    while (parent->GetParent() != parent)
    {
        parent = parent->GetParent();
    }
    return parent;
}

[[nodiscard]] IDependencyNode* DependencyNode::GetParent() const
{
    return _parent;
}

[[nodiscard]] std::vector<IDependencyNode*> DependencyNode::GetChildren(const predicate_expression_t* predicate) const
{
    std::vector<IDependencyNode*> results;
    for (auto* i : _children)
    {
        if (predicate->Invoke(&i))
        {
            results.push_back(i);
        }
    }
    return results;
}

[[nodiscard]] std::vector<IDependencyNode*> DependencyNode::GetChildren() const
{
    std::vector<IDependencyNode*> results;
    results = _children;
    return results;
}

void DependencyNode::SetParent(IDependencyNode* newParent)
{
    if (_parent)
    {
        if (_parent == newParent) return;

        _parent->RemoveChild(this);
    }

    _parent = newParent;
    if (newParent)
    {
        newParent->AddChild(this);
    }
}

bool DependencyNode::AddChild(IDependencyNode* child)
{
    if (child->GetParent()->Equals(this)) return false;

    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end())
    {
        return false;
    }

    _children.push_back(child);
    child->SetParent(this);
    return true;
}

bool DependencyNode::RemoveChild(IDependencyNode* child)
{
    if (!child->GetParent()->Equals(this)) return false;

    auto it = std::find(_children.begin(), _children.end(), child);
    if (it != _children.end())
    {
        (*it)->SetParent(nullptr);
        _children.erase(it);
        return true;
    }

    return false;
}