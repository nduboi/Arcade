#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <functional>
#include <memory>
#include <thread>
#include "EventModule.hpp"
#include "WindowModule.hpp"
#include "GameModule.hpp"
#include "MenuModule.hpp"

class Core {
private:
	typedef enum LogicModule_e {
		GAME,
		MENU,
		TYPE_COUNT,
	} LogicModule_t;

	Loader::LibLoader _displayLoader; ///< Unique pointer to the DisplayLoader LibLoader.
	Loader::LibLoader _gameLoader; ///< Unique pointer to the GameLoader LibLoader.
	Loader::LibLoader _menuLoader; ///< Unique pointer to the GameLoader LibLoader.

	std::vector<std::string> _displayLibPath;
	std::vector<std::string> _gameLibPath;

	LogicModule_t _moduleLoaded;
	int _gameLibIndex = 0;
	int _displayLibIndex = 0;

	IEvent::event_t _lastEvent;

	std::pair<int, int> _getEventDirection() const;

	bool _isEventClick() const;

	void _processClickEvent(int x, int y, int z);

	void _analyze();

	void _compute();

	void _displayGame() const;

	void _display();


	void _refreshLibList();

	void _loadNextGame();

	void _loadNextGraphic();

public:
	std::unique_ptr<WindowModule> display; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<EventModule> event; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<GameModule> game; ///< Unique pointer to the game GameModule.
	std::unique_ptr<MenuModule> menu; ///< Unique pointer to the game GameModule.

	void displayAllLib();

	void loadDisplayModule(const std::string &displayLib);

	void loadGameModule(const std::string &gameLib);

	void loadMenuModule(const std::string &menuLib = "./lib/arcade_menu.so");

	void loop();

	Core();

	~Core();
};

#endif // PROGRAM_HPP
