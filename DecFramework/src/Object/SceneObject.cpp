#include "Object/SceneObject.hpp"
#include "Object/EngineObject.hpp"
#include "IGlobalEnvironment.hpp"

using namespace DecFramework;
using namespace DecFramework::Object;

SceneImpl::SceneImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
    : BaseType::base_implementation_t(gEnv, obj)
{
}

SceneImpl::~SceneImpl() = default;

void SceneImpl::OnCreate()
{
}

void SceneImpl::OnDelete()
{
}

void SceneImpl::OnClone(IEngineObject* oldObject)
{
}