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

	void _display();

	void _displayGame();

	void _refreshLibList();

	void _loadNextGame();

	void _loadNextGraphic();

public:
	std::shared_ptr<IWindow> displayPtr; ///< Unique pointer to the display IWindow.
	std::shared_ptr<WindowModule> display; ///< Unique pointer to the display WindowModule.
	std::shared_ptr<EventModule> event; ///< Unique pointer to the display WindowModule.
	std::shared_ptr<GameModule> game; ///< Shared pointer to the game GameModule.


	void displayAllLib();

	void loadDisplayModule(const std::string &displayLib);

	void loadGameModule(const std::string &gameLib);

	void loop();

	Core();

	~Core();
};

#endif // PROGRAM_HPP
