#ifndef ARCADEALLEGROEVENT_HPP
#define ARCADEALLEGROEVENT_HPP

#include "IEvent.hpp"
#include "IWindow.hpp"
#include <memory>
#include <allegro5/allegro.h>

/**
 * @class arcadeAllegroEvent
 * @brief A class that implements the IEvent interface using Allegro.
 */
class arcadeAllegroEvent : public IEvent {
private:
    std::shared_ptr<IWindow> _window;
    std::pair<int, int> _mousePos;
    std::pair<int, int> _mapSize;

public:
    void init() override;
    IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;
    std::pair<int, int> getMousePos() override;
    void setMapSize(std::pair<int, int> size) override;
    void cleanup() override;
    std::string getUsername() override;
    void renderWrittiing() override;

    arcadeAllegroEvent(std::shared_ptr<IWindow> window);
    ~arcadeAllegroEvent() = default;
};

#endif // ARCADEALLEGROEVENT_HPP