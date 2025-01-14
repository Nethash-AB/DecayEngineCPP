#ifndef DECAYENGINE_OBJECTDATABASE_HPP
#define DECAYENGINE_OBJECTDATABASE_HPP

#include "Database/DatabaseId.hpp"
#include <Database/IObjectDatabase.hpp>
#include <Object/EngineObjectImplementation.hpp>
#include <Database/IDatabaseId.hpp>
#include <unordered_map>
#include <map>
#include <random>

namespace DecCore::Database
{
    class ObjectDatabase final : public DecFramework::Database::IObjectDatabase
    {
        public:
            explicit ObjectDatabase();

            // (TTTT-SSSSSSSS-IIIIIIIIIIIIIIII)
            // T = Type
            // S = SubType
            // I = Instance
            [[nodiscard]] const DecFramework::Database::IDatabaseId* GetDatabaseIdForString(const std::string& idString) const override;

            [[nodiscard]] bool IsValidReference(const DecFramework::Database::IDatabaseId* id) const override;
            [[nodiscard]] DecFramework::Object::IEngineObject* CreateEngineObject(const DecFramework::Database::IDatabaseId* id) override;
            [[nodiscard]] DecFramework::Object::IEngineObject* CreateEngineObject(const DecFramework::Object::EngineObjectType& type,
                const DecFramework::Object::engine_object_subtype_t& subType) override;
            [[nodiscard]] DecFramework::Object::IEngineObject* GetEngineObject(const DecFramework::Database::IDatabaseId* id) const override;
            [[nodiscard]] DecFramework::Object::IEngineObject* CloneEngineObject(DecFramework::Object::IEngineObject* engineObject) override;
            bool DeleteEngineObject(DecFramework::Object::IEngineObject* obj) override;

            void RegisterImplementation(
                const DecFramework::Object::EngineObjectType& type,
                const DecFramework::Object::engine_object_subtype_t& subType,
                DecFramework::Object::Implementation::implementation_create_func_t createFunction) override;
        private:
            using implementation_submap_t =
                std::map<DecFramework::Object::engine_object_subtype_t, DecFramework::Object::Implementation::implementation_create_func_t>;
            using implementation_map_t = std::unordered_map<DecFramework::Object::EngineObjectType, implementation_submap_t>;
            using object_map_t =
                std::unordered_map<const DecFramework::Database::IDatabaseId*, DecFramework::Object::IEngineObject*, Database::DatabaseIdHash>;
            using random_distribution_t = std::uniform_int_distribution<DecFramework::Object::engine_object_instance_t>;

            implementation_map_t _implementationMap;
            object_map_t _objectMap;
            std::random_device _randomDevice;
            std::mt19937_64 _randomEng;
            random_distribution_t _randomDist;

            [[nodiscard]] const DecFramework::Database::IDatabaseId* GetRandomUnusedId(
                DecFramework::Object::EngineObjectType type, DecFramework::Object::engine_object_subtype_t subType);

            bool RegisterEngineObject(DecFramework::Object::IEngineObject* obj);
            bool UnRegisterEngineObject(const DecFramework::Database::IDatabaseId* id);
        protected:
            ~ObjectDatabase() override;
    };
}

#endif //DECAYENGINE_IOBJECTDATABASE_HPP
