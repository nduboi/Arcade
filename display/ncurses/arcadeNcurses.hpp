//
// Created by roussierenoa on 3/26/25.
//

#ifndef ARCADENCURSES_HPP
#define ARCADENCURSES_HPP

#include <IWindow.hpp>
#include "NcursesEncapsulation.hpp"

namespace Game {
	class arcadeNcurses : public IWindow {
	private:
		Game::NcursesEncapsulation _ncurses;
	public:

		void display() override;

		void closeWindow() override;

		bool isOpen() override;

		void clear() override;

		void drawRectangle(int color, std::pair<size_t, size_t> position) override;

		void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;

		void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;

		void setMapSize(std::pair<size_t, size_t> size) override;

		void resizeWindow(size_t x, size_t y) override;

		arcadeNcurses() {};

		~arcadeNcurses() override = default;
	};
}

#endif //ARCADENCURSES_HPP
