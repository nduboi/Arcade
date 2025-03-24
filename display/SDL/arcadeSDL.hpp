/**
 * @file arcadeSDL.hpp
 * @brief Header file for the arcadeSDL class.
 *
 * This file contains the declaration of the arcadeSDL class, which implements the IDisplayModule interface.
 * 
 * @author eliotttesnier
 * @date 3/17/25
 */

#ifndef arcadeSDL_HPP
#define arcadeSDL_HPP

#include "IWindow.hpp"
#include "IEvent.hpp"
#include <string>
#include <SDL2/SDL.h>

/**
 * @class arcadeSDL
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeSDL class provides an implementation of the IDisplayModule interface,
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeSDL : public IWindow {
	std::string _libName = "Arcade SDL2"; ///< The name of the library.
	std::pair<int, int> _mapSize; ///< The size of the map.

private:
	std::pair<int, int> _getWindowPosition(std::pair<int, int> position);
	void _resizeTexture(SDL_Rect &rect, std::pair<int, int> position);

public:
	SDL_Window* _window = nullptr;
	SDL_Renderer* _renderer = nullptr;

	void initWindow() override;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	void drawSprite(std::string asset, int color, std::pair<size_t, size_t> position) override;

	void drawRectangle(int color, std::pair<size_t, size_t> position) override;

	void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

	void setMapSize(std::pair<int, int> size) override;

	arcadeSDL();

	~arcadeSDL();
};

#endif // arcadeSDL_HPP
