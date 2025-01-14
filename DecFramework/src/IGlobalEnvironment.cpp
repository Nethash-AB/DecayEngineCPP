//#include "IGlobalEnvironment.hpp"
//#include "Database/IObjectDatabase.hpp"
//#include "Graph/IDependencyNode.hpp"
//#include "Graph/GraphController.hpp"
//#include "Log/LogController.hpp"
//#include "Object/GameObject.hpp"
//#include "Object/ObjectFactory.hpp"
//#include "Object/SceneObject.hpp"
//#include "Object/WorldObject.hpp"
//
//using namespace DecFramework;
//using namespace DecFramework::Database;
//using namespace DecFramework::Graph;
//using namespace DecFramework::Log;
//using namespace DecFramework::Object;
//
//IGlobalEnvironment::IGlobalEnvironment()
//    : _objectDatabase(new ObjectDatabase(this)), _objectFactory(new ObjectFactory(this)), _graphController(new IGraphController(this)),
//    _logController(new LogController(this))
//{
//    _objectFactory->RegisterImplementation<GameObjectImpl>();
//    _objectFactory->RegisterImplementation<SceneImpl>();
//    _objectFactory->RegisterImplementation<WorldImpl>();
//}
//
//IGlobalEnvironment::~IGlobalEnvironment()
//{
//    delete _objectFactory;
//    delete _objectDatabase;
//    delete _logController;
//}
//
//ObjectDatabase* IGlobalEnvironment::GetObjectDatabase()
//{
//    return _objectDatabase;
//}
//
//ObjectFactory* IGlobalEnvironment::GetObjectFactory()
//{
//    return _objectFactory;
//}
//
//Graph::IGraphController* IGlobalEnvironment::GetGraphController()
//{
//    return _graphController;
//}
//
//LogController* IGlobalEnvironment::GetLogController()
//{
//    return _logController;
//}