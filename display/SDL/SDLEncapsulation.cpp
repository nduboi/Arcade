//
// Created by roussierenoa on 3/27/25.
//

#include "SDLEncapsulation.hpp"

namespace Display {
	SDLEncapsulation::SDLEncapsulation() {
		if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
			std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
		}
		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
				std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
				return;
			}
		}
		if (SDL_NumJoysticks() > 0) {
			SDL_JoystickOpen(0);
		}
		this->window = SDL_CreateWindow("Arcade - SDL2",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			800, 800,
			SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
		if (!this->window) {
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!this->renderer) {
			std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(this->window);
			SDL_Quit();
			return;
		}
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->renderer);
		SDL_RenderPresent(this->renderer);
	}

	void SDLEncapsulation::display() const {
		SDL_RenderPresent(this->renderer);
	}

	void SDLEncapsulation::renderImage(SDL_Texture *texture, SDL_Rect *rect) {
		SDL_RenderCopy(this->renderer, texture, nullptr, rect);
	}

	void SDLEncapsulation::setColor(int color) const {
		switch (color) {
			case 0: SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); break;      // Black
			case 1: SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255); break; // White
			case 2: SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255); break;    // Red
			case 3: SDL_SetRenderDrawColor(this->renderer, 0, 255, 0, 255); break;    // Green
			case 4: SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255); break;    // Blue
			default: SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255); break;     // Default Black
		}

	}

	void SDLEncapsulation::drawRectangle(SDL_Rect rect) const {
		SDL_RenderFillRect(this->renderer, &rect);
	}

	std::pair<int, int> SDLEncapsulation::getWindowSize() const {
		int width = 0;
		int height = 0;
		SDL_GetWindowSize(this->window, &width, &height);
		return {width, height};
	}

	void SDLEncapsulation::resizeWindow(size_t x, size_t y) const
	{
		SDL_SetWindowSize(this->window, static_cast<int>(x), static_cast<int>(y));
	}

	bool SDLEncapsulation::isOpen() const {
		return (this->window != nullptr && this->renderer != nullptr);
	}

	void SDLEncapsulation::clear() const {
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->renderer);
	}

	SDL_Texture * SDLEncapsulation::createTextureFromSurface(SDL_Surface *surface) const {
		return SDL_CreateTextureFromSurface(this->renderer, surface);
	}

	SDLEncapsulation::~SDLEncapsulation() {
		SDL_DestroyRenderer(this->renderer);
		SDL_DestroyWindow(this->window);
		IMG_Quit();
		SDL_Quit();
		this->renderer = nullptr;
		this->window = nullptr;
	}
}