#pragma once

#include <SDL3/SDL.h>

#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
#include <vector>

namespace Rice {

    class EventManager
    {
        public:
            EventManager() = default;
            ~EventManager() = default;

            EventManager(const EventManager&) = delete;
            EventManager& operator=(const EventManager&) = delete;

            /*
            * Poll SDL events and dispatch engine events.
            */
            void poll();

            /*
            * Register a callback for an event type.
            */
            template<typename Event>
            void subscribe(std::function<void(const Event&)> callback)
            {
                m_Listeners[typeid(Event)].push_back(
                    [callback](const std::any& event)
                    {
                        callback(
                            std::any_cast<const Event&>(event)
                        );
                    }
                );
            }

            /*
            * Emit an event manually.
            *
            * This can be used by the engine or by the user
            * to create custom events.
            */
            template<typename Event>
            void emit(const Event& event)
            {
                auto it = m_Listeners.find(typeid(Event));

                if (it == m_Listeners.end())
                    return;

                const std::any data = event;

                for (const auto& callback : it->second)
                {
                    callback(data);
                }
            }

        private:
            using Callback =
                std::function<void(const std::any&)>;

            void processSDLEvent(const SDL_Event& event);

            std::unordered_map<
                std::type_index,
                std::vector<Callback>
            > m_Listeners;
    };

} // namespace Engine