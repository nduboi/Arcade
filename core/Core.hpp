//
// Created by roussierenoa on 4/3/25.
//

#ifndef CORE_HPP
#define CORE_HPP
#include <EventModule.hpp>
#include <GameModule.hpp>
#include <memory>
#include <WindowModule.hpp>
#include "Menu.hpp"
#include "Saver.hpp"
#include "LibLoader.hpp"
#include "Exception.hpp"

class Core {
private:
	enum ModuleType {
		GAME,
		MENU
	};

	ModuleType _loadedModuleType = MENU;
	std::vector<std::string> _displayLibsPaths;
	std::vector<std::string> _gameLibsPaths;

	unsigned int _indexDisplay = 0;
	unsigned int _indexGame = 0;

	IEvent::event_t _lastEvent = IEvent::NOTHING;

	Loader::LibLoader _displayLoader;
	Loader::LibLoader _gameLoader;

	std::shared_ptr<IWindow> _windowPtr;
	std::shared_ptr<WindowModule> _window;
	std::shared_ptr<EventModule> _event;
	std::shared_ptr<GameModule> _game;
	Menu _menu;
	Saver _saver;

	std::pair<int, int> _getEventDirection() const;
	bool _isEventClick();
	void _processClickEvent(int x, int y, int z);

	void _saveScore();
	void _setHighScore();

	void _reloadCurrentGame();

	void _loadDisplayLib(const std::string &path);
	void _switchGraphic();
	void _loadGameLib(const std::string &path);
	void _switchGame();

	void _displayAllLib();
	void _refreshLibPaths();

	void _analyse();

	void _processMenuClick();

	void _compute();
	void _displayGame();
	void _displayMenu();
	void _displayHUD();
	void _display();

public:
	void loop();
	Core(std::string argv);
	~Core();
};

#endif //CORE_HPP
