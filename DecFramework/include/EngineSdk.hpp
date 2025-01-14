#ifndef DECAYENGINE_ENGINESDK_HPP
#define DECAYENGINE_ENGINESDK_HPP

#include "Enum.hpp"
#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>

namespace DecFramework
{
    class IGlobalEnvironment;

    namespace Database
    {
        class IDatabaseId;
        class IObjectDatabase;
    }

    namespace Expression
    {
        template <typename>
        class IExpression;
    }

    namespace Graph
    {
        class IDependencyNode;
        class IGraphController;
    }

    namespace Log
    {
        typedef uint8_t log_severity_t;
        enum struct LogSeverity : log_severity_t;

        inline std::string GetLogSeverityName(const LogSeverity& logSeverity);
        inline std::ostream& operator<<(std::ostream& lhs, const LogSeverity& rhs);

        typedef FlagsEnum<LogSeverity> LogSeverityFlags;

        class Logger;
        class LogController;
    }

    namespace Object
    {
        typedef uint16_t engine_object_type_t;
        typedef uint32_t engine_object_subtype_t;
        typedef uint64_t engine_object_instance_t;

        enum struct EngineObjectType : engine_object_type_t
        {
            Invalid = 0u,
            Resource = 1u,
            Scene = 2u,
            World = 3u,
            GameObject = 4u,
            Component = 5u,
            Property = 6u,

            Min = Resource,
            Max = Property
        };

        class IEngineObject;

        namespace Implementation
        {
            class IEngineObjectImplementation;

            using implementation_create_func_t = IEngineObjectImplementation*(*)(const IGlobalEnvironment*, Object::IEngineObject*);
        }
    }

    namespace SubSystem
    {
        typedef uint64_t subsystem_id_t;

        constexpr subsystem_id_t Framework = 0;
    }

    namespace Tracking
    {
        template <class>
        class DecayObjectTracker;

        class IDecayObject;
    }
}

#ifndef NAMEOF
#define NAMEOF(x) #x
#endif //NAMEOF

#ifndef CURRENT_LOCATION
#define CURRENT_LOCATION() __LINE__, __FUNCTION__, __FILE__
#endif //CURRENT_LOCATION

#ifndef CURRENT_LOCATION_DECL
#define CURRENT_LOCATION_DECL() int lineNumber, std::string callerFunction, std::string sourceFile
#endif //CURRENT_LOCATION_DECL

#ifndef ENGINE_OBJECT_TYPE_RANGE_VALID
#define ENGINE_OBJECT_TYPE_RANGE_VALID(x)\
(x <= DecFramework::Object::EngineObjectType::Max && x >= DecFramework::Object::EngineObjectType::Min)
#endif //ENGINE_OBJECT_TYPE_RANGE_VALID

#ifndef ENGINE_OBJECT_TYPE_RANGE_VALID_SASSERT
#define ENGINE_OBJECT_TYPE_RANGE_VALID_SASSERT(x)\
static_assert(ENGINE_OBJECT_TYPE_RANGE_VALID(x));
#endif //ENGINE_OBJECT_TYPE_RANGE_VALID_SASSERT

#ifndef ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF
#define ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF(x)\
std::enable_if_t<ENGINE_OBJECT_TYPE_RANGE_VALID(x)>*
#endif //ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF

#ifndef ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF_DECL
#define ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF_DECL(x)\
std::enable_if_t<ENGINE_OBJECT_TYPE_RANGE_VALID(x)>* = nullptr
#endif //ENGINE_OBJECT_TYPE_RANGE_VALID_ENABLEIF_DECL

#ifndef FWD_ENGINE_OBJECT
#define FWD_ENGINE_OBJECT()\
namespace DecFramework::Object\
{\
    class IEngineObject;\
    class EngineObject;\
}
#endif //FWD_ENGINE_OBJECT

#ifndef FWD_DATABASE_ID
#define FWD_DATABASE_ID()\
namespace DecFramework::Database\
{\
    class IDatabaseId;\
}
#endif //FWD_DATABASE_ID

#ifndef FWD_OBJECT_DATABASE
#define FWD_OBJECT_DATABASE()\
namespace DecFramework::Database\
{\
    class IObjectDatabase;\
}
#endif //FWD_OBJECT_DATABASE

#ifndef FWD_OBJECT_FACTORY
#define FWD_OBJECT_FACTORY()\
namespace DecFramework::Object\
{\
    class ObjectFactory;\
}
#endif //FWD_OBJECT_FACTORY

#ifndef FWD_GRAPH_CONTROLLER
#define FWD_GRAPH_CONTROLLER()\
namespace DecFramework::Graph\
{\
    class IDependencyNode;\
    class DependencyNode;\
    class GraphController;\
}
#endif //FWD_GRAPH_CONTROLLER

#ifndef FWD_LOG_CONTROLLER
#define FWD_LOG_CONTROLLER()\
namespace DecFramework::Log\
{\
    class Logger;\
    class LogController;\
}
#endif //FWD_LOG_CONTROLLER

#ifndef FWD_GLOBAL_ENVIRONMENT
#define FWD_GLOBAL_ENVIRONMENT()\
namespace DecFramework\
{\
    class GlobalEnvironment;\
}
#endif //FWD_GLOBAL_ENVIRONMENT

#endif //DECAYENGINE_ENGINESDK_HPP
