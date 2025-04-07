//
// Created by roussierenoa on 4/3/25.
//

#include <filesystem>
#include <chrono>
#include <IEntity.hpp>
#include "Core.hpp"

std::pair<int, int> Core::_getEventDirection() const {
	std::pair<int, int> direction = {0, 0};

	if (this->_lastEvent == IEvent::event_t::UP)
		direction = {0, -1};
	if (this->_lastEvent == IEvent::event_t::DOWN)
		direction = {0, 1};
	if (this->_lastEvent == IEvent::event_t::LEFT)
		direction = {-1, 0};
	if (this->_lastEvent == IEvent::event_t::RIGHT)
		direction = {1, 0};
	return direction;
}

bool Core::_isEventClick() {
	return this->_lastEvent == IEvent::event_t::MOUSECLICK ||
		this->_lastEvent == IEvent::event_t::MOUSELEFTCLICK ||
		this->_lastEvent == IEvent::event_t::MOUSERIGHTCLICK;
}

void Core::_processClickEvent(int x, int y, int z)
{
	std::pair<size_t, size_t> gridSize = this->_game->getGridSize();
	this->_event->setMapSize({static_cast<int>(gridSize.first), static_cast<int>(gridSize.second)});

	std::pair<int, int> pos = this->_event->getMousePos();

	if (pos.first != x || pos.second != y)
		return;

	grid_t grid = this->_game->getEntities();
	IEntity *entity = grid[y][x][z].get();

	if (entity == nullptr)
		return;

	clickType_t state = (this->_lastEvent == IEvent::event_t::MOUSELEFTCLICK) ? LEFT_CLICK :
		(this->_lastEvent == IEvent::event_t::MOUSERIGHTCLICK) ? RIGHT_CLICK : MIDDLE_CLICK;
	std::shared_ptr<IGameModule> gameModule = std::static_pointer_cast<IGameModule>(this->_game);
	entity->onClick(gameModule, state);
}

void Core::_saveScore() {
	if (this->_loadedModuleType != GAME)
		return;

	std::size_t highScore = this->_game->getHighScore();
	std::string username = "default";
	std::string game = this->_gameLibsPaths.at(this->_indexGame);

	this->_saver.saveScore(highScore, username, game);
}

void Core::_setHighScore() {
	if (this->_loadedModuleType != GAME)
		return;

	std::string username = "default";
	std::string game = this->_gameLibsPaths.at(this->_indexGame);

	this->_game->setHighScore(this->_saver.getHighScore(username, game));
}

void Core::_reloadCurrentGame() {
	this->_saveScore();
	this->_loadGameLib(this->_gameLibsPaths.at(this->_indexGame));
	this->_setHighScore();
	this->_window->resizeWindow(800, 900);
}

void Core::_loadDisplayLib(const std::string &path) {
	this->_event.reset();
	this->_window.reset();
	this->_windowPtr.reset();
	this->_displayLoader.openLib(path);

	this->_windowPtr = std::shared_ptr<IWindow>(
		this->_displayLoader.initEntryPointPtr<IWindow>("createInstance")
	);
	if (!this->_windowPtr) {
		throw CoreException("Failed to load createDisplay symbol.");
	}
	this->_window = std::make_shared<WindowModule>(this->_windowPtr);
	this->_event = std::make_shared<EventModule>(
		this->_displayLoader.initEntryPointPtr<IEvent>("createEvent", this->_windowPtr)
	);
	if (!this->_event) {
		throw CoreException("Failed to load createEvent symbol.");
	}
	this->_event->init();
#ifdef _DEBUG
	std::cout << "Display library loaded successfully: " << path << std::endl;
#endif
}

void Core::_loadGameLib(const std::string &path) {
	this->_game.reset();
	this->_gameLoader.openLib(path);

	this->_game = std::make_shared<GameModule>(
		this->_gameLoader.initEntryPointPtr<IGameModule>("createGame")
	);
	if (!this->_game) {
		throw CoreException("Failed to load createDisplay symbol.");
	}
#ifdef _DEBUG
	std::cout << "Display library loaded successfully: " << path << std::endl;
#endif
}

void Core::_switchGraphic() {
    if (this->_window) {
        this->_window->closeWindow();
    }
    if (this->_displayLibsPaths.empty()) {
        std::cerr << "No display libraries available." << std::endl;
        return;
    }
    this->_indexDisplay = (this->_indexDisplay == 0) ? this->_displayLibsPaths.size() - 1 : this->_indexDisplay - 1;
    try {
        this->_loadDisplayLib(this->_displayLibsPaths.at(this->_indexDisplay));
#ifdef _DEBUG
        std::cout << "Switched to display library: " << this->_displayLibsPaths.at(this->_indexDisplay) << std::endl;
#endif
	} catch (const std::exception &e) {
        std::cerr << "Failed to switch display library: " << e.what() << std::endl;
    }
	if (this->_loadedModuleType == GAME)
		this->_window->resizeWindow(800, 900);
	else
		this->_window->resizeWindow(1620, 900);
}

void Core::_switchGame() {
	this->_loadedModuleType = GAME;
	if (this->_gameLibsPaths.empty()) {
		std::cerr << "No game libraries available." << std::endl;
		return;
	}
	this->_indexGame = (this->_indexGame == 0) ? this->_gameLibsPaths.size() - 1 : this->_indexGame - 1;
	try {
		this->_loadGameLib(this->_gameLibsPaths.at(this->_indexGame));
#ifdef _DEBUG
		std::cout << "Switched to game library: " << this->_gameLibsPaths.at(this->_indexGame) << std::endl;
#endif
	} catch (const std::exception &e) {
		std::cerr << "Failed to switch game library: " << e.what() << std::endl;
	}
}

void Core::_displayAllLib() {
	std::cout << "Available libraries:" << std::endl;
	std::cout << std::endl;
	std::cout << "  - Display:" << std::endl;
	for (const auto &lib : this->_displayLibsPaths) {
		std::cout << "    - " << lib << std::endl;
	}
	std::cout << std::endl;
	std::cout << "  - Game:" << std::endl;
	for (const auto &lib : this->_gameLibsPaths) {
		std::cout << "    - " << lib << std::endl;
	}
}

void Core::_refreshLibPaths() {
	const std::string libFolder = "./lib";
	Loader::LibLoader libLoader;

	this->_indexGame = 0;
	this->_indexDisplay = 0;
	this->_displayLibsPaths.clear();
	this->_gameLibsPaths.clear();
	try {
		for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
			if (entry.path().extension() == ".so") {
				libLoader.openLib(entry.path().string());
				Loader::ModuleType_t moduleType = libLoader.initEntryPoint<Loader::ModuleType_t>("getType");
				if (moduleType == Loader::GAME_MODULE)
					this->_gameLibsPaths.push_back(entry.path().string());
				if (moduleType == Loader::DISPLAY_MODULE)
					this->_displayLibsPaths.push_back(entry.path().string());
			}
		}
	} catch (const std::filesystem::filesystem_error &e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
	}
}

void Core::_analyse() {
	std::pair<size_t, size_t> gridSize {};

	this->_lastEvent = IEvent::NOTHING;
	if (this->_loadedModuleType == GAME)
		gridSize = this->_game->getGridSize();
	IEvent::event_t event = this->_event->pollEvents(gridSize);
	this->_lastEvent = event;
	if (event == IEvent::event_t::CLOSE)
		this->_window->closeWindow();
	if (event == IEvent::event_t::NEXTGRAPHIC)
		this->_switchGraphic();
	if (event == IEvent::event_t::REFRESH && this->_loadedModuleType == GAME)
		this->_reloadCurrentGame();
	if (event == IEvent::event_t::NEXTGAME) {
		this->_switchGame();
		this->_window->resizeWindow(800, 900);
	}
	if (event == IEvent::event_t::MENU) {
		this->_loadedModuleType = MENU;
		this->_window->resizeWindow(1620, 900);
		this->_window->setMapSize({0, 0});
		this->_event->setMapSize({0, 0});
	}
	if (event == IEvent::event_t::ESCAPE) {
		this->_loadedModuleType = MENU;
		this->_window->resizeWindow(1620, 900);
		this->_window->setMapSize({0, 0});
		this->_event->setMapSize({0, 0});
	}
	if (event == IEvent::event_t::NEXTDIFFICULTY) {
		if (this->_loadedModuleType == GAME) {
			this->_saver.saveScore(this->_game->getHighScore(), "default", this->_gameLibsPaths.at(this->_indexGame));
			this->_game->changeDifficulty();
		}
	}
	if (event == IEvent::event_t::MOUSELEFTCLICK) {
		if (this->_loadedModuleType == MENU) {
			this->_processMenuClick();
		}
	}
}

void Core::_processMenuClick()
{
    if (this->_loadedModuleType != MENU)
        return;

    std::pair<int, int> mousePos = this->_event->getMousePos();

    std::string selectedValue;
    action_e action = this->_menu.handleClick(mousePos.first, mousePos.second, selectedValue);
#ifdef _DEBUG
	std::cout << "Selected value: " << selectedValue << std::endl;
#endif
	if (action == action_e::GRAPHICLIB) {
        for (size_t i = 0; i < this->_displayLibsPaths.size(); i++) {
            if (this->_displayLibsPaths[i].find(selectedValue) != std::string::npos) {
                this->_indexDisplay = i;
                this->_loadDisplayLib(this->_displayLibsPaths[i]);
                break;
            }
        }
    } else if (action == action_e::GAMELIB) {
        for (size_t i = 0; i < this->_gameLibsPaths.size(); i++) {
            if (this->_gameLibsPaths[i].find(selectedValue) != std::string::npos) {
                this->_indexGame = i;
                this->_loadGameLib(this->_gameLibsPaths[i]);
                this->_setHighScore();
                this->_loadedModuleType = GAME;
				this->_window->resizeWindow(800, 900);
                break;
            }
        }
    }
}

void Core::_compute() {
	if (this->_loadedModuleType == GAME) {
		std::shared_ptr<IGameModule> gameModule = std::static_pointer_cast<IGameModule>(this->_game);
		gameModule->update(gameModule);

		grid_t grid = gameModule->getEntities();
		std::pair<size_t, size_t> gridSize = gameModule->getGridSize();

		for (int y = 0; y < gridSize.second; y++) {
			for (int x = 0; x < gridSize.first; x++) {
				for (int z = 0; z < grid[y][x].size(); z++) {
					IEntity *entity = grid[y][x][z].get();
					if (entity == nullptr)
						continue;

					if (this->_isEventClick())
						this->_processClickEvent(x, y, z);

					if (entity->isMovable()) {
						if (entity->isControlable()) {
							entity->moveEntity(gameModule, this->_getEventDirection());
						} else {
							entity->moveEntity(gameModule);
						}
					}
				}
			}
		}
	}
}

void Core::_displayGame() {
	if (this->_loadedModuleType == GAME) {
		grid_t grid = this->_game->getEntities();
		std::pair<size_t, size_t> gridSize = this->_game->getGridSize();

		this->_window->setMapSize({static_cast<int>(gridSize.second), static_cast<int>(gridSize.first)});
		for (int y = 0; y < gridSize.second; y++) {
			for (int x = 0; x < gridSize.first; x++) {
				for (int z = 0; z < grid[y][x].size(); z++) {
					IEntity *entity = grid[y][x][z].get();

					this->_window->drawSprite(entity->getSpriteName(), entity->getColor(), entity->getText(), {x, y});
				}
			}
		}
	}
}

void Core::_displayMenu() {
	if (this->_loadedModuleType == MENU) {
		this->_menu.setSelectedGraphicLib(this->_displayLibsPaths[this->_indexDisplay]);
		this->_menu.displayMenu(this->_windowPtr, this->_menu.getBoxPoses(), this->_displayLibsPaths, this->_gameLibsPaths);
	}
}

void Core::_displayHUD() {
	if (this->_loadedModuleType != GAME)
		return;

	std::vector<std::shared_ptr<IEntity>> hud = this->_game->getHUD();

	for (auto &entity : hud) {
		this->_window->drawText(entity->getText(), entity->getColor(), entity->getPosition());
	}
}

void Core::_display() {
	static std::chrono::time_point<std::chrono::system_clock> last = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;
	if (elapsed_seconds.count() < 0.1)
		return;
	last = now;

	this->_window->clear();
	this->_displayGame();
	this->_displayMenu();
	this->_displayHUD();
	this->_window->display();
}

void Core::loop() {
	while (this->_window->isOpen()) {
		this->_analyse();
		if (!this->_window->isOpen())
			break;
		this->_compute();
		this->_display();
	}
	this->_window->closeWindow();
}

Core::Core(std::string argv): _menu(this->_window), _saver("savefile.json") {
	this->_refreshLibPaths();
	if (argv == "-h" || argv == "--help") {
		std::cout << "Run the program with lib as argument:" << std::endl;
		std::cout << "  ./arcade [lib]" << std::endl;
		this->_displayAllLib();
		throw HelpException();
	}
	this->_loadDisplayLib(argv);
}

Core::~Core() {
	if (this->_game)
		this->_saveScore();
	if (this->_window)
		this->_window->closeWindow();
}
