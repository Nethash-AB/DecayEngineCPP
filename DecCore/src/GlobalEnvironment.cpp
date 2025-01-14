#include "GlobalEnvironment.hpp"
#include "Database/ObjectDatabase.hpp"
#include "Graph/GraphController.hpp"

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Graph;
using namespace DecFramework::Log;
using namespace DecFramework::Object;
using namespace DecFramework::Tracking;

using namespace DecCore;
using namespace DecCore::Database;
using namespace DecCore::Graph;

GlobalEnvironment::GlobalEnvironment()
    : _tracker(DecayObjectTracker(std::shared_ptr<IGlobalEnvironment>(this))),
    _objectDatabase(New<ObjectDatabase>()), _graphController(New<GraphController>())
{
}

GlobalEnvironment::~GlobalEnvironment()
{
    Delete(_objectDatabase);
    Delete(_graphController);
}

[[nodiscard]] IObjectDatabase* GlobalEnvironment::GetObjectDatabase() const
{
    return _objectDatabase;
}

[[nodiscard]] DecFramework::Graph::IGraphController* GlobalEnvironment::GetGraphController() const
{
    return _graphController;
}

[[nodiscard]] DecFramework::Tracking::DecayObjectTracker<> GlobalEnvironment::GetObjectTracker() const
{
    return _tracker;
}