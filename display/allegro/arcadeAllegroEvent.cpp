#include "arcadeAllegroEvent.hpp"
#include "arcadeAllegro.hpp"
#include <iostream>

void arcadeAllegroEvent::init() {
    // Initialize Allegro event handling
}

IEvent::event_t arcadeAllegroEvent::pollEvents(std::pair<int, int> gridSize) {
    ALLEGRO_EVENT event;
    auto allegroWindow = std::dynamic_pointer_cast<arcadeAllegro>(_window);

    if (allegroWindow && al_get_next_event(allegroWindow->allegro->eventQueue, &event)) {
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            return IEvent::CLOSE;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_UP: return IEvent::UP;
                case ALLEGRO_KEY_DOWN: return IEvent::DOWN;
                case ALLEGRO_KEY_LEFT: return IEvent::LEFT;
                case ALLEGRO_KEY_RIGHT: return IEvent::RIGHT;
                case ALLEGRO_KEY_ESCAPE: return IEvent::ESCAPE;
                case ALLEGRO_KEY_SPACE: return IEvent::SPACE;
                case ALLEGRO_KEY_ENTER: return IEvent::ENTER;
                case ALLEGRO_KEY_M: return IEvent::MENU;
                case ALLEGRO_KEY_N: return IEvent::NEXTGRAPHIC;
                case ALLEGRO_KEY_R: return IEvent::REFRESH;
                case ALLEGRO_KEY_G: return IEvent::NEXTGAME;
                case ALLEGRO_KEY_H: return IEvent::NEXTDIFFICULTY;
            }
        }
    }
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeAllegroEvent::getMousePos() {
    return this->_mousePos;
}

void arcadeAllegroEvent::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

void arcadeAllegroEvent::cleanup() {
    // Cleanup Allegro event handling
}

std::string arcadeAllegroEvent::getUsername() {
    return "";
}

void arcadeAllegroEvent::renderWrittiing() {
    // Handle text input if needed
}

arcadeAllegroEvent::arcadeAllegroEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = {0, 0};
    this->_mapSize = {0, 0};
}
