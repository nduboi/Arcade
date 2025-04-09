#include "AllegroEncapsulation.hpp"
#include <stdexcept>
#include <iostream>

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
        if (!al_install_mouse())
            throw std::runtime_error("Failed to initialize Allegro mouse.");
        if (!al_init_image_addon())
            throw std::runtime_error("Failed to initialize Allegro image addon.");
        this->_display = al_create_display(1620, 900);
        al_set_window_title(this->_display, "Arcade - Allegro");
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
        al_register_event_source(this->eventQueue, al_get_mouse_event_source());
    }

    AllegroEncapsulation::~AllegroEncapsulation() {
        for (auto& [_, f] : fontCache) {
            al_destroy_font(f);
        }
        if (this->font) {
            al_destroy_font(this->font);
        }
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

    void AllegroEncapsulation::drawRectangleMenu(const std::pair<size_t, size_t>& size,
        const std::pair<size_t, size_t>& position, const Color& color)
    {
        ALLEGRO_COLOR allegroColor = al_map_rgba(
            color.r,
            color.g,
            color.b,
            255
        );
        al_draw_filled_rectangle(
            position.first,
            position.second,
            position.first + size.first,
            position.second + size.second,
            allegroColor
        );
    }

    void AllegroEncapsulation::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
        ALLEGRO_COLOR outerColor = al_map_rgb(255, 255, 255);
        al_draw_filled_rectangle(position.first, position.second,
            position.first + size.first, position.second + size.second, outerColor);
        ALLEGRO_COLOR innerColor = al_map_rgb(0, 0, 0);
        al_draw_filled_rectangle(position.first + thickness, position.second + thickness,
            position.first + size.first - thickness, position.second + size.second - thickness, innerColor);
    }

    void AllegroEncapsulation::drawText(const std::string& text, int x, int y,
                                        const Color& color, int fontSize) {
        ALLEGRO_COLOR allegroColor = al_map_rgba((uint8_t)color.r, (uint8_t)color.g, (uint8_t)color.b, (uint8_t)color.a);
        const char* fontPath = "assets/ARCADECLASSIC.TTF";
        if (!al_init_font_addon()) {
            std::cerr << "Failed to initialize font addon!" << std::endl;
        }
        if (!al_init_ttf_addon()) {
            std::cerr << "Failed to initialize TTF addon!" << std::endl;
        }
        ALLEGRO_FONT* newFont = al_load_font(fontPath, fontSize, 0);


        if (!newFont) {
            std::cerr << "Using built-in font as fallback" << std::endl;
            al_draw_text(this->font, allegroColor, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
            return;
        }

        al_draw_text(newFont, allegroColor, x, y, ALLEGRO_ALIGN_LEFT, text.c_str());
        al_destroy_font(newFont); // Important to avoid memory leaks
    }

    void AllegroEncapsulation::resizeWindow(int width, int height) {
        al_resize_display(this->_display, width, height);
    }

    std::pair<int, int> AllegroEncapsulation::getWindowSize() {
        return {al_get_display_width(this->_display), al_get_display_height(this->_display)};
    }
}
