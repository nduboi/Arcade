/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
#define IEVENT_HPP_

#include <utility>
#include <string>

class IEvent {
    public:
        typedef enum event_e {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            SPACE,
            ENTER,
            ESCAPE,
            CLOSE,
            NEXTGAME,
            NEXTGRAPHIC,
            REFRESH,
            MOUSECLICK,
            MOUSERIGHTCLICK,
            MOUSELEFTCLICK,
            MENU,
            NOTHING,
            TYPING,
            NEXTDIFFICULTY,
        } event_t;
        virtual ~IEvent() = default;
        virtual void init() = 0;
        virtual event_t pollEvents(std::pair<int, int> gridSize) = 0;
        virtual void cleanup() = 0;
        virtual std::pair<int, int> getMousePos() = 0;
        virtual void setMapSize(std::pair<int, int> size) = 0;

        virtual std::string getUsername() = 0;
        virtual void renderWrittiing() = 0;
};

//extern "C" IEvent *creatEvent(IWindow &window);
#endif /* !IEVENT_HPP_ */
