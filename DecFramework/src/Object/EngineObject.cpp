#include "Object/EngineObject.hpp"
#include "Database/IDatabaseId.hpp"
#include "Graph/IGraphController.hpp"
#include "IGlobalEnvironment.hpp"

using namespace DecFramework;
using namespace DecFramework::Object;
using namespace DecFramework::Object::Implementation;
using namespace DecFramework::Database;

EngineObject::EngineObject(const IGlobalEnvironment* gEnv, const Database::IDatabaseId* id)
    : _gEnv(gEnv), _id(id), _implementation(nullptr), IEngineObject()
{
}

EngineObject::~EngineObject()
{
    delete _id;
}

void EngineObject::SetImplementation(Implementation::IEngineObjectImplementation* implementation)
{
    _implementation = implementation;
}

[[nodiscard]] const Database::IDatabaseId* EngineObject::GetId() const
{
    return _id;
}

[[nodiscard]] Graph::IDependencyNode* EngineObject::GetNode() const
{
    return _gEnv->GetGraphController()->GetNode(_id);
}

[[nodiscard]] Implementation::IEngineObjectImplementation* EngineObject::GetImplementation() const
{
    return _implementation;
}

[[nodiscard]] bool EngineObject::Equals(const IEngineObject* other) const
{
    return other->GetId()->Equals(_id);
}