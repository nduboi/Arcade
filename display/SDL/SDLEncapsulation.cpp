//
// Created by roussierenoa on 3/27/25.
//

#include "SDLEncapsulation.hpp"

namespace Display {
	SDLEncapsulation::SDLEncapsulation() {
#ifdef _DEBUG
		std::cout << "Initializing SDL resources..." << std::endl;
#endif

		if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) < 0) {
				std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
				return;
			}
		}
		if ((IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)) == 0) {
			std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
			SDL_Quit();
			return;
		}
		if (TTF_WasInit() == 0) {
			if (TTF_Init() == -1) {
				std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
				IMG_Quit();
				SDL_Quit();
				return;
			}
		}
		this->window = SDL_CreateWindow("Arcade - SDL2",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1620, 900,
			SDL_WINDOW_SHOWN);
		if (!this->window) {
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
			return;
		}
		this->renderer = SDL_CreateRenderer(this->window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		if (!this->renderer) {
			std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(this->window);
			TTF_Quit();
			IMG_Quit();
			SDL_Quit();
			return;
		}
		this->defaultFont = TTF_OpenFont("assets/Arial.ttf", 20);
		if (!this->defaultFont) {
			std::cerr << "Failed to load default font! SDL_ttf Error: " << TTF_GetError() << std::endl;
		}
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
		SDL_RenderClear(this->renderer);
		SDL_RenderPresent(this->renderer);
#ifdef _DEBUG
		std::cout << "SDL resources initialized successfully." << std::endl;
#endif
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

	void SDLEncapsulation::drawSpriteMenu(const std::pair<float, float>& size,
        const std::string& asset, const std::pair<int, int>& position)
	{
        SDL_Surface* surface = IMG_Load(asset.c_str());
        if (!surface) {
            SDL_Log("Impossible de charger l'image : %s", IMG_GetError());
            return;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        if (!texture) {
            SDL_Log("Impossible de créer la texture : %s", SDL_GetError());
            SDL_FreeSurface(surface);
            return;
        }
        SDL_Rect destRect;
        destRect.x = position.first;
        destRect.y = position.second;
        destRect.w = static_cast<int>(size.first);
        destRect.h = static_cast<int>(size.second);
        SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    void SDLEncapsulation::drawRectangleMenu(const std::pair<size_t, size_t>& size,
        const std::pair<size_t, size_t>& position, const Color& color)
	{
        SDL_Color sdlColor = {
            static_cast<Uint8>(color.r),
            static_cast<Uint8>(color.g),
            static_cast<Uint8>(color.b),
            255
        };
        SDL_SetRenderDrawColor(this->renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
        SDL_Rect rect;
        rect.x = position.first;
        rect.y = position.second;
        rect.w = size.first;
        rect.h = size.second;
        SDL_RenderFillRect(this->renderer, &rect);
    }

    void SDLEncapsulation::drawThickRectangle(const std::pair<int, int>& position,
        const std::pair<int, int>& size, int thickness)
	{
        SDL_Rect outerRect = {
            position.first,
            position.second,
            static_cast<int>(size.first),
            static_cast<int>(size.second)
        };
        SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(this->renderer, &outerRect);
        SDL_Rect innerRect = {
            position.first + thickness,
            position.second + thickness,
            static_cast<int>(size.first - 2 * thickness),
            static_cast<int>(size.second - 2 * thickness)
        };
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(this->renderer, &innerRect);
    }

    void SDLEncapsulation::drawTextMenu(const std::string& text,
        const std::pair<size_t, size_t>& position,
		const Color& color, int charSize)
	{
        TTF_Font* font = (charSize == 20 && defaultFont)
            ? defaultFont
            : TTF_OpenFont("assets/ARCADECLASSIC.TTF", charSize);
        if (!font) {
            SDL_Log("Impossible de charger la police : %s", TTF_GetError());
            return;
        }
        SDL_Color sdlColor = {
            static_cast<Uint8>(color.r),
            static_cast<Uint8>(color.g),
            static_cast<Uint8>(color.b),
            255
        };
        SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
        if (!surface) {
            SDL_Log("Impossible de créer la surface de texte : %s", TTF_GetError());
            if (font != defaultFont) TTF_CloseFont(font);
            return;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        if (!texture) {
            SDL_Log("Impossible de créer la texture de texte : %s", SDL_GetError());
            SDL_FreeSurface(surface);
            if (font != defaultFont) TTF_CloseFont(font);
            return;
        }

        SDL_Rect destRect;
        destRect.x = position.first;
        destRect.y = position.second;
        destRect.w = surface->w;
        destRect.h = surface->h;
        SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        if (font != defaultFont) TTF_CloseFont(font);
    }

    void SDLEncapsulation::drawText(const std::string& text,
        int color, const std::pair<size_t, size_t>& position)
	{
        if (!defaultFont)
            return;

        SDL_Color sdlColor = {255, 255, 255, 255};
        switch (color)
        {
            case 0: sdlColor = {0, 0, 0, 255}; break;      // Black
            case 1: sdlColor = {255, 255, 255, 255}; break; // White
            case 2: sdlColor = {255, 0, 0, 255}; break;    // Red
            case 3: sdlColor = {0, 255, 0, 255}; break;    // Green
            case 4: sdlColor = {0, 0, 255, 255}; break;    // Blue
        }
        SDL_Surface* surface = TTF_RenderText_Blended(defaultFont, text.c_str(), sdlColor);
        if (!surface) {
            SDL_Log("Impossible de créer la surface de texte : %s", TTF_GetError());
            return;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);
        if (!texture) {
            SDL_Log("Impossible de créer la texture de texte : %s", SDL_GetError());
            SDL_FreeSurface(surface);
            return;
        }
        SDL_Rect destRect;
        destRect.x = position.first;
        destRect.y = position.second;
        destRect.w = surface->w;
        destRect.h = surface->h;
        SDL_RenderCopy(this->renderer, texture, NULL, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

	SDLEncapsulation::~SDLEncapsulation() {
#ifdef _DEBUG
        std::cout << "Destroying SDL resources..." << std::endl;
#endif
		if (defaultFont) {
			TTF_CloseFont(defaultFont);
			defaultFont = nullptr;
		}
		if (renderer) {
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}
		if (window) {
			SDL_DestroyWindow(window);
			window = nullptr;
        }
		if (TTF_WasInit())
			TTF_Quit();
		if (IMG_Init(0))
			IMG_Quit();
		if (SDL_WasInit(SDL_INIT_VIDEO))
			SDL_Quit();
#ifdef _DEBUG
        std::cout << "SDL resources destroyed successfully." << std::endl;
#endif
    }
}