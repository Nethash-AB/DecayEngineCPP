#ifndef DECAYENGINE_GRAPHCONTROLLER_HPP
#define DECAYENGINE_GRAPHCONTROLLER_HPP

#include "Database/DatabaseId.hpp"
#include <Graph/IGraphController.hpp>
#include <unordered_map>

namespace DecCore::Graph
{
    class GraphController : public DecFramework::Graph::IGraphController
    {
        public:
            explicit GraphController();

            DecFramework::Graph::IDependencyNode* CreateNode(const DecFramework::Database::IDatabaseId* id) override;
            [[nodiscard]] DecFramework::Graph::IDependencyNode* GetNode(const DecFramework::Database::IDatabaseId* id) const override;
            bool DeleteNode(DecFramework::Graph::IDependencyNode* node) override;
        private:
            using node_map_t = std::unordered_map<const DecFramework::Database::IDatabaseId*, DecFramework::Graph::IDependencyNode*, Database::DatabaseIdHash>;

            node_map_t _nodeMap;
        protected:
            ~GraphController() override;
    };
}

#endif //DECAYENGINE_IGRAPHCONTROLLER_HPP
