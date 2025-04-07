//
// Created by roussierenoa on 3/26/25.
//

#ifndef ARCADENCURSES_HPP
#define ARCADENCURSES_HPP

#include <IWindow.hpp>
#include "NcursesEncapsulation.hpp"

namespace Display {
	class arcadeNcurses : public IWindow {
	private:
		std::pair<size_t, size_t> _mapSize;
		Display::NcursesEncapsulation _ncurses;
	public:

		void display() override;

		void closeWindow() override;

		bool isOpen() override;

		void clear() override;

		void drawRectangle(int color, std::pair<size_t, size_t> position) override;

		void drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) override;

		void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) override;

		void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

		void drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) override;

		void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;

		void drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) override;

		void setMapSize(std::pair<size_t, size_t> size) override;

		void resizeWindow(size_t x, size_t y) override;

		std::pair<int, int> getWindowSize() override;

		std::pair<int, int> getMapSize() const {return this->_mapSize;};

		bool isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) override;

		arcadeNcurses();

		~arcadeNcurses() override = default;
	};
}

#endif //ARCADENCURSES_HPP
