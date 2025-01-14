#ifndef DECAYENGINE_IGLOBALENVIRONMENT_HPP
#define DECAYENGINE_IGLOBALENVIRONMENT_HPP

#include "Database/IObjectDatabase.hpp"
#include "Graph/IGraphController.hpp"
//#include "Log/LogController.hpp"
#include "Tracking/DecayObjectTracker.hpp"
#include "EngineSdk.hpp"

namespace DecFramework
{
    class IGlobalEnvironment
    {
        public:
            [[nodiscard]] virtual Database::IObjectDatabase* GetObjectDatabase() const = 0;
            [[nodiscard]] virtual Graph::IGraphController* GetGraphController() const = 0;
//            [[nodiscard]] virtual Log::LogController* GetLogController() const = 0;

            template <typename TObj, typename... TArgs>
            [[nodiscard]] std::enable_if_t<std::is_base_of_v<Tracking::IDecayObject, TObj>, TObj*> New(TArgs... args) const
            {
                return GetObjectTracker().CreateObject<TObj, TArgs...>(args...);
            }

            void Delete(Tracking::IDecayObject* obj) const
            {
                return GetObjectTracker().DestroyObject(obj);
            }
        protected:
            [[nodiscard]] virtual Tracking::DecayObjectTracker<> GetObjectTracker() const = 0;
    };
}

#endif //DECAYENGINE_IGLOBALENVIRONMENT_HPP
