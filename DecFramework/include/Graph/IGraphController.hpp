#ifndef DECAYENGINE_IGRAPHCONTROLLER_HPP
#define DECAYENGINE_IGRAPHCONTROLLER_HPP

#include "Tracking/IDecayObject.hpp"
#include "EngineSdk.hpp"

namespace DecFramework::Graph
{
    class IGraphController : public Tracking::IDecayObject
    {
        public:
            virtual Graph::IDependencyNode* CreateNode(const Database::IDatabaseId* id) = 0;
            [[nodiscard]] virtual Graph::IDependencyNode* GetNode(const Database::IDatabaseId* id) const = 0;
            virtual bool DeleteNode(Graph::IDependencyNode* node) = 0;
        protected:
            ~IGraphController() override = default;
    };
}

#endif //DECAYENGINE_IGRAPHCONTROLLER_HPP
