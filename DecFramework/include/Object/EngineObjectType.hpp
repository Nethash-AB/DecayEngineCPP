#ifndef DECAYENGINE_ENGINEOBJECTTYPE_HPP
#define DECAYENGINE_ENGINEOBJECTTYPE_HPP

#include "EngineSdk.hpp"

namespace DecFramework::Object
{
    inline std::string GetEngineObjectTypeName(const EngineObjectType& objType)
    {
        switch (objType)
        {
            case EngineObjectType::Resource:
                return "Resource";
            case EngineObjectType::Scene:
                return "Scene";
            case EngineObjectType::World:
                return "World";
            case EngineObjectType::GameObject:
                return "GameObject";
            case EngineObjectType::Component:
                return "Component";
            case EngineObjectType::Property:
                return "Property";
            default:
                return "Invalid";
        }
    }

    inline std::ostream& operator<<(std::ostream& lhs, const EngineObjectType& rhs)
    {
        return lhs << GetEngineObjectTypeName(rhs);
    }

    inline constexpr bool IsSubtypedType(Object::EngineObjectType type)
    {
        return type == Object::EngineObjectType::Resource || type == Object::EngineObjectType::Component || type == Object::EngineObjectType::Property;
    }
}

#endif //DECAYENGINE_ENGINEOBJECTTYPE_HPP
