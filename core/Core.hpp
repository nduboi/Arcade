#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <memory>
#include "EventModule.hpp"
#include "WindowModule.hpp"
#include "GameModule.hpp"

class Core {
private:
	Loader::LibLoader _displayLoader; ///< Unique pointer to the DisplayLoader LibLoader.
	Loader::LibLoader _gameLoader; ///< Unique pointer to the GameLoader LibLoader.

public:
	std::unique_ptr<WindowModule> display; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<EventModule> event; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<GameModule> game; ///< Unique pointer to the game GameModule.

	void displayAllLib();

	void loadDisplayModule(const std::string &displayLib);

	void loadGameModule(const std::string &gameLib);

	Core();

	~Core();
};

#endif // PROGRAM_HPP

