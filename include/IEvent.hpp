/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
#define IEVENT_HPP_

#include <utility>

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
            MENU,
            REFRESH,
            MOUSECLICK,
            NOTHING,
        } event_t;
        virtual ~IEvent() = default;
        virtual void init() = 0;
        virtual event_t pollEvents(std::pair<int, int> gridSize) = 0;
        virtual void cleanup() = 0;
        virtual std::pair<int, int> getMousePos() = 0;
    protected:
    private:
};

//extern "C" IEvent *creatEvent(IWindow &window);
#endif /* !IEVENT_HPP_ */
