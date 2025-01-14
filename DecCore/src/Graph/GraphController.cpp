#include "Graph/GraphController.hpp"
#include "Graph/DependencyNode.hpp"
#include <Exception/DependencyNodeNotFoundException.hpp>
#include <IGlobalEnvironment.hpp>

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Graph;
using namespace DecFramework::Log;

using namespace DecCore;
using namespace DecCore::Graph;

GraphController::GraphController()
    : _nodeMap()
{
}

GraphController::~GraphController()
{
    for (auto it : _nodeMap)
    {
        GetGEnv()->Delete(it.second);
    }
}

IDependencyNode* GraphController::CreateNode(const IDatabaseId* id)
{
    auto it = _nodeMap.find(id);
    if (it != _nodeMap.end())
    {
        std::ostringstream stream;
        stream << "Dependency Node for ";
        stream << "(" << id->ToString() << ") ";
        stream << "has already been created, returning existing instance.";

        // ToDo: RENABLE THIS
//        GetGEnv()->GetLogController()->Print(LogMessage{SubSystem::Framework, LogSeverity::Warning, stream.str(), CURRENT_LOCATION()});
        return it->second;
    }

    IDependencyNode* node = GetGEnv()->New<DependencyNode>(id);
    _nodeMap.insert(std::make_pair(id, node));
    return node;
}

[[nodiscard]] IDependencyNode* GraphController::GetNode(const IDatabaseId* id) const
{
    auto it = _nodeMap.find(id);
    if (it != _nodeMap.end())
    {
        return it->second;
    }
    throw DependencyNodeNotFoundException(id, CURRENT_LOCATION());
}

bool GraphController::DeleteNode(IDependencyNode* node)
{
    auto it = _nodeMap.find(node->GetId());
    if (it != _nodeMap.end())
    {
        _nodeMap.erase(it);
        GetGEnv()->Delete(it->second);
        return true;
    }

    return false;
}