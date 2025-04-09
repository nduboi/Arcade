#include "arcadeXlibEvent.hpp"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/keysym.h>

void arcadeXlibEvent::init() {
    // Nothing specific to initialize
}

IEvent::event_t arcadeXlibEvent::pollEvents(std::pair<int, int> gridSize) {
    auto xlibWindow = std::dynamic_pointer_cast<arcadeXlib>(this->_window);
    if (!xlibWindow || !xlibWindow->xlib) {
        return IEvent::NOTHING;
    }
    
    Display *display = xlibWindow->xlib->getDisplay();
    Window window = xlibWindow->xlib->getWindow();
    
    // Check if there are pending events
    if (XPending(display) > 0) {
        XEvent event;
        XNextEvent(display, &event);
        
        switch (event.type) {
            case Expose:
                // Window needs redrawing
                return IEvent::NOTHING;
                
            case KeyPress: {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                
                if (this->_iswritting) {
                    char buffer[32];
                    int count;
                    count = XLookupString(&event.xkey, buffer, sizeof(buffer), NULL, NULL);
                    
                    if (count > 0 && this->_input.length() <= 15) {
                        this->_input += std::string(buffer, count);
                    }
                    
                    if (key == XK_BackSpace && !this->_input.empty()) {
                        this->_input.pop_back();
                    }
                    
                    return IEvent::NOTHING;
                }
                
                // Map keys to arcade events
                switch (key) {
                    case XK_Up:     return IEvent::UP;
                    case XK_Down:   return IEvent::DOWN;
                    case XK_Left:   return IEvent::LEFT;
                    case XK_Right:  return IEvent::RIGHT;
                    case XK_Escape: return IEvent::ESCAPE;
                    case XK_space:  return IEvent::SPACE;
                    case XK_Return: return IEvent::ENTER;
                    case XK_g:      return IEvent::NEXTGAME;
                    case XK_r:      return IEvent::REFRESH;
                    case XK_n:      return IEvent::NEXTGRAPHIC;
                    case XK_m:      return IEvent::MENU;
                    case XK_h:      return IEvent::NEXTDIFFICULTY;
                    case XK_q:      return IEvent::CLOSE;
                }
                break;
            }
                
            case ButtonPress: {
                if (event.xbutton.button == Button1) {
                    // Update mouse position
                    this->_mousePos.first = event.xbutton.x;
                    this->_mousePos.second = event.xbutton.y;
                    
                    // Check if clicking in the username field (similar to SDL implementation)
                    if (this->_mousePos.first >= 725 && this->_mousePos.first <= 900 && 
                        this->_mousePos.second >= 120 && this->_mousePos.second <= 160) {
                        this->_iswritting = true;
                    }
                    
                    return IEvent::MOUSELEFTCLICK;
                } else if (event.xbutton.button == Button3) {
                    this->_mousePos.first = event.xbutton.x;
                    this->_mousePos.second = event.xbutton.y;
                    return IEvent::MOUSERIGHTCLICK;
                } else if (event.xbutton.button == Button2) {
                    this->_mousePos.first = event.xbutton.x;
                    this->_mousePos.second = event.xbutton.y;
                    return IEvent::MOUSECLICK;
                }
                break;
            }
            
            case MotionNotify:
                // Update mouse position for tracking hover state
                this->_mousePos.first = event.xmotion.x;
                this->_mousePos.second = event.xmotion.y;
                break;
                
            case ClientMessage:
                // Handle window close button
                if (event.xclient.data.l[0] == XInternAtom(display, "WM_DELETE_WINDOW", False)) {
                    return IEvent::CLOSE;
                }
                break;
        }
    }
    
    // No event to report
    return IEvent::NOTHING;
}

std::pair<int, int> arcadeXlibEvent::getMousePos() {
    return this->_mousePos;
}

void arcadeXlibEvent::setMapSize(std::pair<int, int> size) {
    this->_mapSize = size;
}

void arcadeXlibEvent::cleanup() {
    // Nothing specific to clean up
}

std::string arcadeXlibEvent::getUsername() {
    return this->_input;
}

void arcadeXlibEvent::renderWrittiing() {
    this->_window->drawTextMenu(
        _input,
        {685, 407},
        {0, 0, 0},
        24
    );
}

arcadeXlibEvent::arcadeXlibEvent(std::shared_ptr<IWindow> window) : _window(window) {
    this->_mousePos = std::make_pair(0, 0);
    this->_mapSize = std::make_pair(0, 0);
    this->_iswritting = false;
}
