//#include "Graph/GraphController.hpp"
//#include "Exception/DependencyNodeNotFoundException.hpp"
//#include "Graph/IDependencyNode.hpp"
//#include "Log/LogController.hpp"
//#include "IGlobalEnvironment.hpp"
//
//using namespace DecFramework;
//using namespace DecFramework::Database;
//using namespace DecFramework::Exception;
//using namespace DecFramework::Graph;
//using namespace DecFramework::Log;
//
//IGraphController::GraphController(IGlobalEnvironment* gEnv)
//    : _gEnv(gEnv), _nodeMap()
//{
//}
//
//IGraphController::~GraphController()
//{
//    for (auto it : _nodeMap)
//    {
//        delete it.second;
//    }
//}
//
//IDependencyNode* IGraphController::CreateNode(const IDatabaseId* id)
//{
//    auto it = _nodeMap.find(id);
//    if (it != _nodeMap.end())
//    {
//        std::ostringstream stream;
//        stream << "Dependency Node for ";
//        stream << "(" << id->ToString() << ") ";
//        stream << "has already been created, returning existing instance.";
//
//        _gEnv->GetLogController()->Print(LogMessage{SubSystem::Framework, LogSeverity::Warning, stream.str(), CURRENT_LOCATION()});
//        return it->second;
//    }
//
//    IDependencyNode* node = new DependencyNode(_gEnv, id);
//    _nodeMap.insert(std::make_pair(id, node));
//    return node;
//}
//
//[[nodiscard]] Graph::IDependencyNode* IGraphController::GetNode(const Database::IDatabaseId* id) const
//{
//    auto it = _nodeMap.find(id);
//    if (it != _nodeMap.end())
//    {
//        return it->second;
//    }
//    throw DependencyNodeNotFoundException(id, CURRENT_LOCATION());
//}
//
//bool IGraphController::DeleteNode(Graph::IDependencyNode* node)
//{
//    auto it = _nodeMap.find(node->GetId());
//    if (it != _nodeMap.end())
//    {
//        _nodeMap.erase(it);
//        delete it->second;
//        return true;
//    }
//
//    return false;
//}