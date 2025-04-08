#include "AllegroEncapsulation.hpp"
#include <stdexcept>
#include <allegro5/allegro_image.h>

namespace Display {
    AllegroEncapsulation::AllegroEncapsulation() {
        if (!al_init())
            throw std::runtime_error("Failed to initialize Allegro.");
        if (!al_init_primitives_addon())
            throw std::runtime_error("Failed to initialize Allegro primitives addon.");
        if (!al_init_font_addon())
            throw std::runtime_error("Failed to initialize Allegro font addon.");
        if (!al_install_keyboard())
            throw std::runtime_error("Failed to initialize Allegro keyboard.");
        if (!al_init_image_addon())
            throw std::runtime_error("Failed to initialize Allegro image addon.");

        this->_display = al_create_display(800, 600);
        if (!this->_display)
            throw std::runtime_error("Failed to create Allegro display.");

        this->font = al_create_builtin_font();
        if (!this->font)
            throw std::runtime_error("Failed to create Allegro font.");

        this->eventQueue = al_create_event_queue();
        if (!this->eventQueue)
            throw std::runtime_error("Failed to create Allegro event queue.");

        al_register_event_source(this->eventQueue, al_get_display_event_source(this->_display));
        al_register_event_source(this->eventQueue, al_get_keyboard_event_source());
    }

    AllegroEncapsulation::~AllegroEncapsulation() {
        if (this->font)
            al_destroy_font(this->font);
        if (this->_display)
            al_destroy_display(this->_display);
    }

    void AllegroEncapsulation::display() {
        al_flip_display();
    }

    bool AllegroEncapsulation::isOpen() {
        return this->_display != nullptr;
    }

    void AllegroEncapsulation::clear() {
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    void AllegroEncapsulation::setColor(const Color& color) {
        al_draw_filled_rectangle(0, 0, 0, 0, al_map_rgba(color.r, color.g, color.b, color.a)); // Placeholder
    }

    void AllegroEncapsulation::drawRectangle(int x, int y, int width, int height) {
        al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255));
    }

    void AllegroEncapsulation::drawText(const std::string& text, int x, int y, const Color& color, int fontSize) {
        ALLEGRO_COLOR allegroColor = al_map_rgba(color.r, color.g, color.b, color.a);
        al_draw_text(this->font, allegroColor, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
    }

    void AllegroEncapsulation::resizeWindow(int width, int height) {
        al_resize_display(this->_display, width, height);
    }

    std::pair<int, int> AllegroEncapsulation::getWindowSize() {
        return {al_get_display_width(this->_display), al_get_display_height(this->_display)};
    }
}
