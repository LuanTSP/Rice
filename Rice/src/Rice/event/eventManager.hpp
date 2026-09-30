#pragma once

#include <SDL3/SDL.h>

#include <any>
#include <functional>
#include <typeindex>
#include <unordered_map>
namespace RICE_INTERNAL {

class EventManager
{
public:
    EventManager() = default;
    ~EventManager() = default;

    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    void poll();

    template<typename Event, typename Callable>
    void subscribe(Callable&& callable)
    {
        m_Listeners[typeid(Event)].push_back(
            [callback = std::forward<Callable>(callable)](
                const std::any& data
            )
            {
                callback(
                    std::any_cast<const Event&>(data)
                );
            }
        );
    }

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
    using EventCallback =
        std::function<void(const std::any&)>;

    void processSDLEvent(const SDL_Event& event);

    std::unordered_map<
        std::type_index,
        std::vector<EventCallback>
    > m_Listeners;
};

} // namespace Rice