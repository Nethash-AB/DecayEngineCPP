#include "Database/ObjectDatabase.hpp"
#include <Exception/ArgumentOutOfRangeException.hpp>
#include <Exception/EngineObjectImplementationAlreadyRegisteredException.hpp>
#include <Exception/EngineObjectImplementationNotFoundException.hpp>
#include <Exception/EngineObjectNotFoundException.hpp>
#include <Exception/FormatException.hpp>
#include <Object/EngineObject.hpp>
#include <Util/String.hpp>
#include <IGlobalEnvironment.hpp>
#include <limits>

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Log;
using namespace DecFramework::Object;
using namespace DecFramework::Object::Implementation;
using namespace DecFramework::Object::Implementation::Feature;
using namespace DecFramework::Util::String;

using namespace DecCore;
using namespace DecCore::Database;

ObjectDatabase::ObjectDatabase()
    : _implementationMap(), _objectMap(),
    _randomDevice(std::random_device()), _randomEng(std::mt19937_64(_randomDevice())),
    _randomDist(random_distribution_t(0, std::numeric_limits<DecFramework::Object::engine_object_instance_t>::max()))
{
    for (engine_object_type_t i = static_cast<engine_object_type_t>(EngineObjectType::Min); i <= static_cast<engine_object_type_t>(EngineObjectType::Max); i++)
    {
        _implementationMap[EngineObjectType{i}] = implementation_submap_t();
    }
}

ObjectDatabase::~ObjectDatabase()
{
    for (auto it : _objectMap)
    {
        delete it.second;
    }
}

[[nodiscard]] const IDatabaseId* ObjectDatabase::GetDatabaseIdForString(const std::string& idString) const
{
    const int expectedTypeStringLength = sizeof(std::underlying_type_t<EngineObjectType>) * 2;
    const int expectedSubTypeStringLength = sizeof(engine_object_subtype_t) * 2;
    const int expectedInstanceStringLength = sizeof(engine_object_instance_t) * 2;

    std::string id = Trim(idString);
    const int expectedTotalLength = expectedTypeStringLength + expectedSubTypeStringLength + expectedInstanceStringLength + 2;
    int totalLength = id.length();
    if (totalLength != expectedTotalLength)
    {
        throw ArgumentException(
            std::string("Invalid " NAMEOF(DatabaseId) " length. Expected (") +
            std::to_string(expectedTotalLength) + ") but received (" +
            std::to_string(totalLength) +
            std::string(")."),
            NAMEOF(idString), CURRENT_LOCATION());
    }

    // Parts
    std::vector<std::string> parts = Split(id, '-');
    const int expectedTotalPartCount = 3;
    int partCount = parts.size();
    if (partCount != expectedTotalPartCount)
    {
        throw ArgumentException(
            std::string("Invalid " NAMEOF(DatabaseId) " length. Expected (") +
            std::to_string(expectedTotalPartCount) + " parts) but received (" +
            std::to_string(partCount) +
            std::string(" parts)."),
            NAMEOF(idString), CURRENT_LOCATION());
    }

    // Type
    std::string typeString = parts[0];
    int typeStringLength = typeString.length();
    if (typeStringLength != expectedTypeStringLength)
    {
        throw ArgumentException(
            std::string("Invalid " NAMEOF(DatabaseId) " length. Expected 'type' part length (") +
            std::to_string(expectedTypeStringLength) + ") but received (" +
            std::to_string(typeStringLength) +
            std::string(")."),
            NAMEOF(idString), CURRENT_LOCATION());
    }
    for (int i = 0; i < expectedTypeStringLength; i++)
    {
        if (!isxdigit(typeString[i]))
        {
            throw FormatException("Invalid " NAMEOF(DatabaseId) " format. Non-hexadecimal characters in 'type' part.", CURRENT_LOCATION());
        }
    }
    EngineObjectType type = EngineObjectType{(std::underlying_type_t<EngineObjectType>) std::stoi(typeString, nullptr, 16)};
    if (!ENGINE_OBJECT_TYPE_RANGE_VALID(type))
    {
        throw ArgumentOutOfRangeException(NAMEOF(EngineObjectType) " is out of range.", NAMEOF(idString), CURRENT_LOCATION());
    }

    // SubType
    std::string subTypeString = parts[1];
    int subTypeStringLength = subTypeString.length();
    if (subTypeStringLength != expectedSubTypeStringLength)
    {
        throw ArgumentException(
            std::string("Invalid " NAMEOF(DatabaseId) " length. Expected 'subType' part length (") +
            std::to_string(expectedSubTypeStringLength) + ") but received (" +
            std::to_string(subTypeStringLength) +
            std::string(")."),
            NAMEOF(idString), CURRENT_LOCATION());
    }
    for (int i = 0; i < expectedSubTypeStringLength; i++)
    {
        if (!isxdigit(subTypeString[i]))
        {
            throw FormatException("Invalid " NAMEOF(DatabaseId) " format. Non-hexadecimal characters in 'subType' part.", CURRENT_LOCATION());
        }
    }
    engine_object_subtype_t subType = std::stoi(subTypeString, nullptr, 16);

    // Instance
    std::string instanceString = parts[2];
    int instanceStringLength = instanceString.length();
    if (instanceStringLength != expectedInstanceStringLength)
    {
        throw ArgumentException(
            std::string("Invalid " NAMEOF(DatabaseId) " length. Expected 'instance' part length (") +
            std::to_string(expectedInstanceStringLength) + ") but received (" +
            std::to_string(instanceStringLength) +
            std::string(")."),
            NAMEOF(idString), CURRENT_LOCATION());
    }
    for (int i = 0; i < expectedInstanceStringLength; i++)
    {
        if (!isxdigit(instanceString[i]))
        {
            throw FormatException("Invalid " NAMEOF(DatabaseId) " format. Non-hexadecimal characters in 'instance' part.", CURRENT_LOCATION());
        }
    }
    engine_object_instance_t instance = std::stoi(instanceString, nullptr, 16);

    return new DatabaseId(type, subType, instance, false);
}

[[nodiscard]] bool ObjectDatabase::IsValidReference(const IDatabaseId* id) const
{
    return _objectMap.count(id) > 0;
}

[[nodiscard]] IEngineObject* ObjectDatabase::CreateEngineObject(const IDatabaseId* id)
{
    auto it = _implementationMap[id->GetType()].find(id->GetSubType());
    if (it != _implementationMap[id->GetType()].end())
    {
        if (IsValidReference(id))
        {
            std::ostringstream stream;
            stream << "Engine Object ";
            stream << "(" << id->ToString() << ") ";
            stream << "has already been registered, returning existing instance.";

            // ToDo: RENABLE THIS
//            _gEnv->GetLogController()->Print(LogMessage{SubSystem::Framework, LogSeverity::Warning, stream.str(), CURRENT_LOCATION()});
            return GetEngineObject(id);
        }

        EngineObject* obj = new EngineObject(GetGEnv(), id);
        IEngineObjectImplementation* impl = (*it->second)(GetGEnv(), obj);
        obj->SetImplementation(impl);

        RegisterEngineObject(obj);
        GetGEnv()->GetGraphController()->CreateNode(obj->GetId());

        if (impl->HasFeature<CreateCallbackFeature>())
        {
            impl->TryInvokeFeature<CreateCallbackFeature>();
        }

        return obj;
    }
    throw EngineObjectImplementationNotFoundException(id->GetType(), id->GetSubType(), CURRENT_LOCATION());
}

[[nodiscard]] IEngineObject* ObjectDatabase::CreateEngineObject(const EngineObjectType& type, const engine_object_subtype_t& subType)
{
    if (!ENGINE_OBJECT_TYPE_RANGE_VALID(type))
    {
        throw ArgumentOutOfRangeException(NAMEOF(EngineObjectType) " is out of range.", NAMEOF(idString), CURRENT_LOCATION());
    }

    auto it = _implementationMap[type].find(subType);
    if (it != _implementationMap[type].end())
    {
        const IDatabaseId *id = GetRandomUnusedId(type, subType);

        EngineObject *obj = new EngineObject(GetGEnv(), id);
        IEngineObjectImplementation* impl = (*it->second)(GetGEnv(), obj);
        obj->SetImplementation(impl);

        RegisterEngineObject(obj);
        GetGEnv()->GetGraphController()->CreateNode(obj->GetId());

        if (impl->HasFeature<CreateCallbackFeature>())
        {
            impl->TryInvokeFeature<CreateCallbackFeature>();
        }

        return obj;
    }
    throw EngineObjectImplementationNotFoundException(type, subType, CURRENT_LOCATION());
}

[[nodiscard]] IEngineObject* ObjectDatabase::GetEngineObject(const IDatabaseId* id) const
{
    auto result = _objectMap.find(id);
    if (result != _objectMap.end())
    {
        return result->second;
    }

    throw EngineObjectNotFoundException(id, CURRENT_LOCATION());
}

[[nodiscard]] IEngineObject* ObjectDatabase::CloneEngineObject(IEngineObject* engineObject)
{
    const IDatabaseId* oldId = engineObject->GetId();
    const IDatabaseId* newId = GetRandomUnusedId(oldId->GetType(), oldId->GetSubType());

    EngineObject* newEngineObject = new EngineObject(GetGEnv(), newId);
    IEngineObjectImplementation* newImpl = (*_implementationMap[newId->GetType()][newId->GetSubType()])(GetGEnv(), newEngineObject);
    newEngineObject->SetImplementation(newImpl);

    RegisterEngineObject(newEngineObject);
    GetGEnv()->GetGraphController()->CreateNode(newEngineObject->GetId());

    if (newImpl->HasFeature<CreateCallbackFeature>())
    {
        newImpl->TryInvokeFeature<CreateCallbackFeature>();
    }

    if (newImpl->HasFeature<CloneCallbackFeature>())
    {
        newImpl->TryInvokeFeature<CloneCallbackFeature>(engineObject);
    }

    return newEngineObject;
}

bool ObjectDatabase::DeleteEngineObject(IEngineObject* obj)
{
    if (!IsValidReference(obj->GetId()))
    {
        delete obj;
        return false;
    }

    IEngineObjectImplementation* impl = obj->GetImplementation();
    if (impl->HasFeature<DeleteCallbackFeature>())
    {
        impl->TryInvokeFeature<DeleteCallbackFeature>();
    }

    if(UnRegisterEngineObject(obj->GetId()))
    {
        delete obj;
        return true;
    }

    delete obj;
    return false;
}

void ObjectDatabase::RegisterImplementation(const EngineObjectType& type, const engine_object_subtype_t& subType, implementation_create_func_t createFunction)
{
    if (_implementationMap[type].count(subType) > 0)
    {
        throw EngineObjectImplementationAlreadyRegisteredException(type, subType, CURRENT_LOCATION());
    }
    _implementationMap[type][subType] = createFunction;
}

const IDatabaseId* ObjectDatabase::GetRandomUnusedId(EngineObjectType type, engine_object_subtype_t subType)
{
    const IDatabaseId* id = nullptr;
    do
    {
        delete id;
        engine_object_instance_t instance = _randomDist(_randomEng);
        id = new DatabaseId(type, subType, instance, true);
    }
    while (IsValidReference(id));

    return id;
}

bool ObjectDatabase::RegisterEngineObject(IEngineObject* obj)
{
    if (IsValidReference(obj->GetId()))
    {
        return false;
    }

    _objectMap.insert(std::make_pair(obj->GetId(), obj));
    return true;
}

bool ObjectDatabase::UnRegisterEngineObject(const IDatabaseId* id)
{
    auto it = _objectMap.find(id);
    if (it != _objectMap.end())
    {
        _objectMap.erase(it);
        return true;
    }

    return false;
}