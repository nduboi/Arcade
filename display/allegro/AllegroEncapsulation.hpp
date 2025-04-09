#ifndef ALLEGROENCAPSULATION_HPP
#define ALLEGROENCAPSULATION_HPP

#include <string>
#include <unordered_map>
#include <utility>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

namespace Display {
    struct Color {
        uint8_t r, g, b, a = 255;
    };
    class AllegroEncapsulation {
    private:
        ALLEGRO_DISPLAY* _display;
        ALLEGRO_FONT* font;
        std::unordered_map<int, ALLEGRO_FONT*> fontCache;

    public:
        ALLEGRO_EVENT_QUEUE *eventQueue;
        AllegroEncapsulation();
        ~AllegroEncapsulation();

        void display();
        bool isOpen();
        void clear();
        void setColor(const Color& color);
        void drawRectangle(int x, int y, int width, int height);

        void drawRectangleMenu(const std::pair<size_t, size_t> &size, const std::pair<size_t, size_t> &position,
                               const Color &color);
        void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness);

        void drawText(const std::string& text, int x, int y, const Color& color, int fontSize);
        void resizeWindow(int width, int height);
        std::pair<int, int> getWindowSize();
    };
}

#endif // ALLEGROENCAPSULATION_HPP
