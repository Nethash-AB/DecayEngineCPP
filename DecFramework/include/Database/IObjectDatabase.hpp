#ifndef DECAYENGINE_IOBJECTDATABASE_HPP
#define DECAYENGINE_IOBJECTDATABASE_HPP

#include "Object/EngineObjectImplementation.hpp"
#include "Tracking/IDecayObject.hpp"
#include "EngineSdk.hpp"

FWD_ENGINE_OBJECT()

namespace DecFramework::Database
{
    class IObjectDatabase : public Tracking::IDecayObject
    {
        public:
            [[nodiscard]] virtual const Database::IDatabaseId* GetDatabaseIdForString(const std::string& idString) const = 0;
            [[nodiscard]] virtual bool IsValidReference(const Database::IDatabaseId* id) const = 0;
            [[nodiscard]] virtual Object::IEngineObject* CreateEngineObject(const Database::IDatabaseId* id) = 0;
            [[nodiscard]] virtual Object::IEngineObject* CreateEngineObject(const Object::EngineObjectType& type,
                const Object::engine_object_subtype_t& subType) = 0;
            [[nodiscard]] virtual Object::IEngineObject* GetEngineObject(const Database::IDatabaseId* id) const = 0;
            [[nodiscard]] virtual Object::IEngineObject* CloneEngineObject(Object::IEngineObject* engineObject) = 0;
            virtual bool DeleteEngineObject(Object::IEngineObject* obj) = 0;

            virtual void RegisterImplementation(
                const Object::EngineObjectType& type,
                const Object::engine_object_subtype_t& subType,
                Object::Implementation::implementation_create_func_t createFunction) = 0;

            template <typename TImpl, std::enable_if_t<Object::Implementation::IsValidImplementation<TImpl>>* = nullptr>
            void RegisterImplementation()
            {
                RegisterImplementationInternal(TImpl::BaseType::Type, TImpl::BaseType::SubType, Implementation::CreateFunction::Get<TImpl>());
            }
        protected:
            ~IObjectDatabase() override = default;
    };
}

#endif //DECAYENGINE_IOBJECTDATABASE_HPP
