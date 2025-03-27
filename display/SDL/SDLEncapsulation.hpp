//
// Created by roussierenoa on 3/27/25.
//

#ifndef SDLENCAPSULATION_HPP
#define SDLENCAPSULATION_HPP

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace Display {
	class SDLEncapsulation {
	private:
		SDL_Window *window = nullptr;
		SDL_Renderer *renderer = nullptr;
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

		SDLEncapsulation();

		~SDLEncapsulation();
	};
}



#endif //SDLENCAPSULATION_HPP
