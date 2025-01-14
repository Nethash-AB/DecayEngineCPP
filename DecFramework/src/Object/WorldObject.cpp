#include "Object/WorldObject.hpp"
#include "Object/EngineObject.hpp"
#include "IGlobalEnvironment.hpp"

using namespace DecFramework;
using namespace DecFramework::Object;

WorldImpl::WorldImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
    : BaseType::base_implementation_t(gEnv, obj)
{
}

WorldImpl::~WorldImpl() = default;

void WorldImpl::OnCreate()
{
}

void WorldImpl::OnDelete()
{
}

void WorldImpl::OnClone(IEngineObject* oldObject)
{
}