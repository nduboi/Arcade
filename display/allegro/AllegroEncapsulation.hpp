#ifndef ALLEGROENCAPSULATION_HPP
#define ALLEGROENCAPSULATION_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <utility>

namespace Display {
    struct Color {
        uint8_t r, g, b, a = 255;
    };
    class AllegroEncapsulation {
    private:
        ALLEGRO_DISPLAY* _display;
        ALLEGRO_FONT* font;

    public:
        ALLEGRO_EVENT_QUEUE *eventQueue;
        AllegroEncapsulation();
        ~AllegroEncapsulation();

        void display();
        bool isOpen();
        void clear();
        void setColor(const Color& color);
        void drawRectangle(int x, int y, int width, int height);
        void drawText(const std::string& text, int x, int y, const Color& color, int fontSize);
        void resizeWindow(int width, int height);
        std::pair<int, int> getWindowSize();
    };
}

#endif // ALLEGROENCAPSULATION_HPP
