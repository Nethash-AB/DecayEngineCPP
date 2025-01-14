#ifndef DECAYENGINE_GLOBALENVIRONMENT_HPP
#define DECAYENGINE_GLOBALENVIRONMENT_HPP

#include <IGlobalEnvironment.hpp>
#include <vector>

namespace DecCore
{
    class GlobalEnvironment : public DecFramework::IGlobalEnvironment
    {
        public:
            explicit GlobalEnvironment();
            ~GlobalEnvironment();

            [[nodiscard]] DecFramework::Database::IObjectDatabase* GetObjectDatabase() const override;
            [[nodiscard]] DecFramework::Graph::IGraphController* GetGraphController() const override;
//            [[nodiscard]] DecFramework::Log::LogController* GetLogController() const override;
        protected:
            [[nodiscard]] DecFramework::Tracking::DecayObjectTracker<> GetObjectTracker() const override;
        private:
            const DecFramework::Tracking::DecayObjectTracker<> _tracker;
            DecFramework::Database::IObjectDatabase* _objectDatabase;
            DecFramework::Graph::IGraphController* _graphController;
//            Log::LogController* _logController;
    };
}

#endif //DECAYENGINE_IGLOBALENVIRONMENT_HPP
