#include "arcadeAllegroEvent.hpp"
#include "arcadeAllegro.hpp"
#include <iostream>

void arcadeAllegroEvent::init()
{
}

IEvent::event_t arcadeAllegroEvent::pollEvents(std::pair<int, int> gridSize)
{
    (void)gridSize;
    ALLEGRO_EVENT event;
    auto allegroWindow = std::dynamic_pointer_cast<arcadeAllegro>(_window);

    if (allegroWindow && al_get_next_event(allegroWindow->allegro->eventQueue, &event)) {

        if (this->_iswritting) {
            if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
                if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                    if (!this->_input.empty())
                        this->_input.pop_back();
                    return IEvent::NOTHING;
                }
                if (this->_input.length() <= 15 && event.keyboard.unichar >= 32 && event.keyboard.unichar <= 126) {
                    this->_input += static_cast<char>(event.keyboard.unichar);
                    return IEvent::NOTHING;
                }
            }
        }
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
                case ALLEGRO_KEY_Q: return IEvent::CLOSE;
            }
        }
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            this->_mousePos.first = event.mouse.x;
            this->_mousePos.second = event.mouse.y;
            if (this->_mousePos.first >= 725 && this->_mousePos.first <= 900 &&
                this->_mousePos.second >= 120 && this->_mousePos.second <= 180) {
                this->_iswritting = true;
            }
            switch (event.mouse.button) {
                case 1: return IEvent::MOUSELEFTCLICK;    // Left button
                case 2: return IEvent::MOUSERIGHTCLICK;   // Right button
                case 3: return IEvent::MOUSECLICK;        // Middle button
                default: return IEvent::MOUSECLICK;
            }
        }
    }
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeAllegroEvent::getMousePos() {
    auto allegroWindow = std::dynamic_pointer_cast<arcadeAllegro>(this->_window);
    const int hudOffset = 100;

    if (!al_is_mouse_installed()) {
        return std::make_pair(-1, -1);
    }
    ALLEGRO_MOUSE_STATE mouse_state;
    al_get_mouse_state(&mouse_state);
    if (this->_mapSize.first > 0 && this->_mapSize.second > 0) {
        auto WinSize = allegroWindow->allegro->getWindowSize();
        return {
            (this->_mousePos.first * this->_mapSize.first) / WinSize.first,
            ((this->_mousePos.second - hudOffset) * this->_mapSize.second) / (WinSize.second - hudOffset)
        };
    }
    return std::make_pair(mouse_state.x, mouse_state.y);
}

void arcadeAllegroEvent::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

void arcadeAllegroEvent::cleanup() {
}

std::string arcadeAllegroEvent::getUsername() {
    return this->_input;
}

void arcadeAllegroEvent::renderWrittiing() {
    this->_window->drawTextMenu(
        this->_input,
        {685, 407},
        {0, 0, 0},
        24
    );
}

arcadeAllegroEvent::arcadeAllegroEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = {0, 0};
    this->_mapSize = {0, 0};
}
