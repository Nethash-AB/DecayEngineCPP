#ifndef DECAYENGINE_DATABASEID_HPP
#define DECAYENGINE_DATABASEID_HPP

#include <Database/IDatabaseId.hpp>

namespace DecCore::Database
{
    class DatabaseId final : public DecFramework::Database::IDatabaseId
    {
        public:
            explicit DatabaseId(
                const DecFramework::Object::EngineObjectType& type,
                const DecFramework::Object::engine_object_subtype_t& subType,
                const DecFramework::Object::engine_object_instance_t& instance, const bool& isRuntimeInstance);
            ~DatabaseId() override;

            [[nodiscard]] DecFramework::Object::EngineObjectType GetType() const override;
            [[nodiscard]] DecFramework::Object::engine_object_subtype_t GetSubType() const override;
            [[nodiscard]] DecFramework::Object::engine_object_instance_t GetInstance() const override;
            [[nodiscard]] bool IsRuntimeInstance() const override;
            [[nodiscard]] bool IsInstanceOf(const IDatabaseId& other) const override;
            [[nodiscard]] std::string ToString() const override;

            [[nodiscard]] bool Equals(const IDatabaseId* other) const override;
        private:
            const DecFramework::Object::EngineObjectType _type;
            const DecFramework::Object::engine_object_subtype_t _subType;
            const DecFramework::Object::engine_object_instance_t _instance;
            const bool _isRuntimeInstance;
    };

    struct DatabaseIdHash final
    {
        std::size_t operator()(const DecFramework::Database::IDatabaseId* id) const;
    };
}

#endif //DECAYENGINE_DATABASEID_HPP
