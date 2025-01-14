#include "Object/GameObject.hpp"
#include "Object/EngineObject.hpp"
#include "IGlobalEnvironment.hpp"

using namespace DecFramework;
using namespace DecFramework::Object;

GameObjectImpl::GameObjectImpl(IGlobalEnvironment* gEnv, Object::IEngineObject* obj)
    : BaseType::base_implementation_t(gEnv, obj)
{
}

GameObjectImpl::~GameObjectImpl() = default;

void GameObjectImpl::OnCreate()
{
}

void GameObjectImpl::OnDelete()
{
}

void GameObjectImpl::OnClone(IEngineObject* oldObject)
{
}