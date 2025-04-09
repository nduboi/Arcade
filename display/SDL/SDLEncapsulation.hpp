//
// Created by roussierenoa on 3/27/25.
//

#ifndef SDLENCAPSULATION_HPP
#define SDLENCAPSULATION_HPP

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <utility>

namespace DisplayLib {
	struct Color {
        uint8_t r, g, b, a = 255;
    };

	class SDLEncapsulation {
	private:
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
		TTF_Font *defaultFont = nullptr;
	public:
		void resizeWindow(size_t x, size_t y) const;

		bool isOpen() const;

		void clear() const;

		SDL_Texture *createTextureFromSurface(SDL_Surface *surface) const;

		void display() const;

		void renderImage(SDL_Texture *texture, SDL_Rect *rect);

		void setColor(int color) const;

		void drawRectangle(SDL_Rect rect) const;

		std::pair<int, int> getWindowSize() const;

		void drawSpriteMenu(const std::pair<float, float>& size,
            const std::string& asset, const std::pair<int, int>& position);

        void drawRectangleMenu(const std::pair<size_t, size_t>& size,
            const std::pair<size_t, size_t>& position, const Color& color);

        void drawThickRectangle(const std::pair<int, int>& position,
            const std::pair<int, int>& size, int thickness);

        void drawTextMenu(const std::string& text,
            const std::pair<size_t, size_t>& position,
			const Color& color = {255, 255, 255}, int charSize = 20);

        void drawText(const std::string& text,
            int color, const std::pair<size_t, size_t>& position);

		SDLEncapsulation();

		~SDLEncapsulation();
	};
}

#endif //SDLENCAPSULATION_HPP
