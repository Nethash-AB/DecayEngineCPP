#include "Database/DatabaseId.hpp"
#include <Exception/ArgumentOutOfRangeException.hpp>
#include <Object/EngineObjectType.hpp>
#include <Util/String.hpp>

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Exception;
using namespace DecFramework::Object;
using namespace DecFramework::Util::String;

using namespace DecCore;
using namespace DecCore::Database;

DatabaseId::DatabaseId(const Object::EngineObjectType& type, const Object::engine_object_subtype_t& subType,
    const engine_object_instance_t& instance, const bool& isRuntimeInstance)
    : _type(type), _subType(Object::IsSubtypedType(type) ? subType : 0), _instance(instance), _isRuntimeInstance(isRuntimeInstance)
{
    if (!ENGINE_OBJECT_TYPE_RANGE_VALID(type))
    {
        throw ArgumentOutOfRangeException(NAMEOF(EngineObjectType) " is out of range.", NAMEOF(idString), CURRENT_LOCATION());
    }
}

DatabaseId::~DatabaseId() = default;

[[nodiscard]] EngineObjectType DatabaseId::GetType() const
{
    return _type;
}

[[nodiscard]] engine_object_subtype_t DatabaseId::GetSubType() const
{
    return _subType;
}

[[nodiscard]] engine_object_instance_t DatabaseId::GetInstance() const
{
    return _instance;
}

[[nodiscard]] bool DatabaseId::IsRuntimeInstance() const
{
    return _isRuntimeInstance;
}

[[nodiscard]] bool DatabaseId::IsInstanceOf(const IDatabaseId& other) const
{
    return _type == other.GetType() && _subType == other.GetSubType();
}

[[nodiscard]] std::string DatabaseId::ToString() const
{
    std::ostringstream outputStream;

    if (IsRuntimeInstance())
    {
        outputStream << "(R)";
    }

    outputStream <<
        Util::String::ToHexString((std::underlying_type_t<EngineObjectType>) GetType()) << "-" <<
        Util::String::ToHexString(GetSubType()) << "-" <<
        Util::String::ToHexString(GetInstance());

    return outputStream.str();
}

[[nodiscard]] bool DatabaseId::Equals(const IDatabaseId* other) const
{
    return _type == other->GetType()
        && _subType == other->GetSubType()
        && _instance == other->GetInstance()
        && _isRuntimeInstance == other->IsRuntimeInstance();
}

template <class T>
inline void CombineHash(std::size_t& size, const T& value)
{
    std::hash<T> hash;
    size ^= hash(value) + 0x9e3779b9u + (size << 6u) + (size >> 2u);
}

std::size_t DatabaseIdHash::operator()(const IDatabaseId* id) const
{
    std::size_t result = 0;
    if (IsSubtypedType(id->GetType()))
    {
        CombineHash(result, id->GetSubType());
    }

    CombineHash(result, id->GetInstance());
    CombineHash<unsigned short>(result, id->IsRuntimeInstance());
    return result;
}