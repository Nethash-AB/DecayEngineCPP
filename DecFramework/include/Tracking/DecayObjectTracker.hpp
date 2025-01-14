#ifndef DECAYENGINE_DECAYOBJECTTRACKER_HPP
#define DECAYENGINE_DECAYOBJECTTRACKER_HPP

#include "Tracking/IDecayObject.hpp"
#include "EngineSdk.hpp"
#include <utility>

namespace DecFramework::Tracking
{
    template <class TAllocator = std::allocator<IDecayObject>>
    class DecayObjectTracker final
    {
        private:
            using allocator_t = TAllocator;
            const std::shared_ptr<IGlobalEnvironment> _gEnv;
        public:
            explicit DecayObjectTracker(std::shared_ptr<IGlobalEnvironment> gEnv) : _gEnv(std::move(gEnv)) {}

            ~DecayObjectTracker() = default;

            template <typename TObj, typename... TArgs>
            std::enable_if_t<std::is_base_of_v<IDecayObject, TObj>, TObj*> CreateObject(TArgs... args)
            {
                std::shared_ptr<IGlobalEnvironment> gEnv = _gEnv;

                using alloc_t = typename std::allocator_traits<allocator_t>::template rebind_alloc<TObj>;
                alloc_t allocator;

                TObj* obj = allocator.allocate(1);
                new ((void*) obj) TObj(std::forward<TArgs>(args)...);
                static_cast<IDecayObject*>(obj)->SetGEnv(gEnv);

                return obj;
            }

            template <typename TObj>
            std::enable_if_t<std::is_base_of_v<IDecayObject, TObj>> DestroyObject(TObj* obj)
            {
                using alloc_t = typename std::allocator_traits<allocator_t>::template rebind_alloc<TObj>;
                alloc_t allocator;

                allocator.deallocate(obj, 1);
                obj = nullptr;
            }
    };
}

#endif //DECAYENGINE_DECAYOBJECTTRACKER_HPP
