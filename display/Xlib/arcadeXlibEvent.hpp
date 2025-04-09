#ifndef ARCADEXLIBEVENT_HPP
#define ARCADEXLIBEVENT_HPP

#include "IEvent.hpp"
#include "IWindow.hpp"
#include <memory>
#include "arcadeXlib.hpp"

class arcadeXlibEvent : public IEvent {
private:
    std::shared_ptr<IWindow> _window;
    std::pair<int, int> _mapSize;
    std::pair<int, int> _mousePos;
    std::string _input;
    bool _iswritting;

public:
    void init() override;
    IEvent::event_t pollEvents(std::pair<int, int> gridSize) override;
    std::pair<int, int> getMousePos() override;
    void setMapSize(std::pair<int, int> size) override;
    void cleanup() override;
    
    std::string getUsername();
    void renderWrittiing();
    
    arcadeXlibEvent(std::shared_ptr<IWindow> window);
    ~arcadeXlibEvent() = default;
};

#endif //ARCADEXLIBEVENT_HPP
