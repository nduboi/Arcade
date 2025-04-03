//
// Created by roussierenoa on 3/17/25.
//

#include <filesystem>
#include <iostream>
#include <cstring>
#include <vector>
#include "Core.hpp"
#include "IEntity.hpp"

Core::Core() : _menu(this->display), _saver("savefile.json") {
	this->_refreshLibList();
	this->_lastEvent = IEvent::event_t::NOTHING;
	this->_moduleLoaded = MENU;
}

Core::~Core() {
	if (this->game)
		this->_saveScore();
	if (this->display)
		this->display->closeWindow();
	this->event.reset();
	this->display.reset();
	this->displayPtr.reset();
}

void Core::_analyze() {
	std::pair<size_t, size_t> gridSize {};

	if (this->_moduleLoaded == GAME)
		gridSize = this->game->getGridSize();
	IEvent::event_t event = this->event->pollEvents(gridSize);
	this->_lastEvent = IEvent::event_t::NOTHING;

	if (event == IEvent::event_t::CLOSE)
		this->display->closeWindow();
	if (event == IEvent::event_t::NEXTGRAPHIC)
		this->_loadNextGraphic();
	if (event == IEvent::event_t::REFRESH && this->_moduleLoaded == GAME)
		this->_reloadCurrentGame();
	if (event == IEvent::event_t::NEXTGAME)
		this->_loadNextGame();
	if (event == IEvent::event_t::MENU) {
		this->_moduleLoaded = MENU;
		display->resizeWindow(1620, 900);
		display->setMapSize({0, 0});
		this->event->setMapSize({0, 0});
	}
	if (event == IEvent::event_t::ESCAPE) {
		this->_moduleLoaded = MENU;
		display->resizeWindow(1620, 900);
	}
	if (event == IEvent::event_t::NEXTDIFFICULTY) {
		if (this->_moduleLoaded == GAME) {
			this->_saver.saveScore(this->game->getHighScore(), "default", this->_gameLibPath.at(this->_gameLibIndex));
			this->game->changeDifficulty();
		}
	}
	if (event == IEvent::event_t::MOUSELEFTCLICK) {
		if (this->_moduleLoaded == MENU) {
			this->_processMenuClick();
		}
	}
	this->_lastEvent = event;
}

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

bool Core::_isEventClick() const {
	return this->_lastEvent == IEvent::event_t::MOUSECLICK ||
		this->_lastEvent == IEvent::event_t::MOUSELEFTCLICK ||
		this->_lastEvent == IEvent::event_t::MOUSERIGHTCLICK;
}

void Core::_processClickEvent(int x, int y, int z) {
	std::pair<size_t, size_t> gridSize = this->game->getGridSize();
	this->event->setMapSize({static_cast<int>(gridSize.second), static_cast<int>(gridSize.first)});

	std::pair<int, int> pos = this->event->getMousePos();

	if (pos.first != x || pos.second != y)
		return;

	grid_t grid = this->game->getEntities();
	IEntity *entity = grid[y][x][z].get();

	if (entity == nullptr)
		return;

	clickType_t state = (this->_lastEvent == IEvent::event_t::MOUSELEFTCLICK) ? LEFT_CLICK :
		(this->_lastEvent == IEvent::event_t::MOUSERIGHTCLICK) ? RIGHT_CLICK : MIDDLE_CLICK;
	std::shared_ptr<IGameModule> gameModule = std::static_pointer_cast<IGameModule>(this->game);
	entity->onClick(gameModule, state);
}

void Core::_processMenuClick()
{
    if (this->_moduleLoaded != MENU)
        return;

    std::pair<int, int> mousePos = this->event->getMousePos();

    std::string selectedValue;
    action_e action = this->_menu.handleClick(mousePos.first, mousePos.second, selectedValue);

	std::cout << "Selected value: " << selectedValue << std::endl;
    if (action == action_e::GRAPHICLIB) {
        for (size_t i = 0; i < this->_displayLibPath.size(); i++) {
            if (this->_displayLibPath[i].find(selectedValue) != std::string::npos) {
                this->_displayLibIndex = i;
                this->loadDisplayModule(this->_displayLibPath[i]);
                break;
            }
        }
    } else if (action == action_e::GAMELIB) {
        for (size_t i = 0; i < this->_gameLibPath.size(); i++) {
            if (this->_gameLibPath[i].find(selectedValue) != std::string::npos) {
                this->_gameLibIndex = i;
                this->loadGameModule(this->_gameLibPath[i]);
                this->_setHighScore();
                this->_moduleLoaded = GAME;
				this->display->resizeWindow(800, 900);
                break;
            }
        }
    }
}

void Core::_compute() {
	if (this->_moduleLoaded == GAME) {
		std::shared_ptr<IGameModule> gameModule = std::static_pointer_cast<IGameModule>(this->game);
		gameModule->update(gameModule);

		grid_t grid = gameModule->getEntities();
		std::pair<size_t, size_t> gridSize = gameModule->getGridSize();

		for (int y = 0; y < gridSize.first; y++) {
			for (int x = 0; x < gridSize.second; x++) {
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

void Core::_display() {
	static std::chrono::time_point<std::chrono::system_clock> last = std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = now - last;
	if (elapsed_seconds.count() < 0.1)
		return;
	last = now;

	this->display->clear();
	this->_displayGame();
	this->_displayMenu();
	this->_displayHUD();
	this->display->display();
}

void Core::_displayGame()
{
	if (this->_moduleLoaded == GAME) {
		grid_t grid = this->game->getEntities();
		std::pair<size_t, size_t> gridSize = this->game->getGridSize();

		this->display->setMapSize({static_cast<int>(gridSize.second), static_cast<int>(gridSize.first)});
		for (int y = 0; y < gridSize.first; y++) {
			for (int x = 0; x < gridSize.second; x++) {
				for (int z = 0; z < grid[y][x].size(); z++) {
					IEntity *entity = grid[y][x][z].get();

					this->display->drawSprite(entity->getSpriteName(), entity->getColor(), entity->getText(), {x, y});
				}
			}
		}
	}
}

void Core::_displayMenu()
{
	if (this->_moduleLoaded == MENU) {
		this->_menu.setSelectedGraphicLib(this->_displayLibPath[this->_displayLibIndex]);
		this->_menu.displayMenu(this->displayPtr, this->_menu.getBoxPoses(), this->_displayLibPath, this->_gameLibPath);
	}
}

void Core::_displayHUD() {
	if (this->_moduleLoaded != GAME)
		return;

	std::vector<std::shared_ptr<IEntity>> hud = this->game->getHUD();

	for (auto &entity : hud) {
		this->display->drawText(entity->getText(), entity->getColor(), entity->getPosition());
	}
}

void Core::_refreshLibList() {
	const std::string libFolder = "./lib";
	Loader::LibLoader libLoader;

	this->_gameLibIndex = 0;
	this->_displayLibIndex = 0;
	this->_displayLibPath.clear();
	this->_gameLibPath.clear();
	try {
		for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
			if (entry.path().extension() == ".so") {
				libLoader.openLib(entry.path().string());
				if (libLoader.getModuleType() == Loader::GAME_MODULE)
					this->_gameLibPath.push_back(entry.path().string());
				if (libLoader.getModuleType() == Loader::DISPLAY_MODULE)
					this->_displayLibPath.push_back(entry.path().string());
				libLoader.closeLib();
			}
		}
	} catch (const std::filesystem::filesystem_error &e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
	}
}

void Core::_loadNextGame() {
	if (this->_gameLibPath.size() == 1 && this->_moduleLoaded == GAME)
		return;
	this->_saveScore();
	this->_gameLibIndex++;
	if (this->_gameLibIndex >= this->_gameLibPath.size())
		this->_gameLibIndex = 0;
	if (strcmp(this->_gameLoader.getModulePath(), "") != 0 && std::filesystem::canonical(this->_gameLibPath.at(this->_gameLibIndex)) == std::filesystem::canonical(this->_gameLoader.getModulePath()))
		return this->_loadNextGame();
	this->loadGameModule(this->_gameLibPath.at(this->_gameLibIndex));
	this->_setHighScore();
	this->display->resizeWindow(800, 900);
}

void Core::_loadNextGraphic() {
	if (this->_displayLibPath.size() == 1)
		return;
	this->_displayLibIndex++;
	if (this->_displayLibIndex >= this->_displayLibPath.size())
		this->_displayLibIndex = 0;
	if (std::filesystem::canonical(this->_displayLibPath.at(this->_displayLibIndex)) == std::filesystem::canonical(this->_displayLoader.getModulePath()))
		return this->_loadNextGraphic();
	this->loadDisplayModule(this->_displayLibPath.at(this->_displayLibIndex));
	if (this->_moduleLoaded == GAME)
		this->display->resizeWindow(800, 900);
	else
		this->display->resizeWindow(1620, 900);
}

void Core::_reloadCurrentGame() {
	this->_saveScore();
	this->loadGameModule(this->_gameLibPath.at(this->_gameLibIndex));
	this->_setHighScore();
	this->display->resizeWindow(800, 900);
}

void Core::displayAllLib()
{
	std::cout << "Display lib:" << std::endl;
	for (auto s: this->_displayLibPath)
		std::cout << "  " << s << std::endl;

	std::cout << std::endl;
	std::cout << "Game lib:" << std::endl;
	for (auto s: this->_gameLibPath)
		std::cout << "  " << s << std::endl;
}

void Core::loadDisplayModule(const std::string &path)
{
	if (this->display)
		this->display->closeWindow();
	this->event.reset();
	this->display.reset();
	this->displayPtr.reset();
	this->_displayLoader.closeLib();
	this->_displayLoader.openLib(path);
	if (this->_displayLoader.getModuleType() != Loader::DISPLAY_MODULE)
		throw CoreException("Error the library loaded is not a Display Module");
	this->displayPtr.reset(this->_displayLoader.initEntryPointDisplay());
	this->display = std::make_shared<WindowModule>(displayPtr);
	this->event = std::make_shared<EventModule>(this->_displayLoader.initEntryPointEvent(this->displayPtr));
	this->event->init();
	for (int i = 0; i < this->_displayLibPath.size(); i++) {
		if (std::filesystem::canonical(this->_displayLibPath.at(i)) == std::filesystem::canonical(this->_displayLoader.getModulePath()))
			this->_displayLibIndex = i;
	}
}

void Core::loadGameModule(const std::string &path) {
	this->game.reset();
	this->_gameLoader.closeLib();
	this->_gameLoader.openLib(path.c_str());
	if (this->_gameLoader.getModuleType() != Loader::GAME_MODULE)
		throw CoreException("Error the library loaded is not a Game Module");
	this->_moduleLoaded = GAME;
	this->game = std::make_unique<GameModule>(this->_gameLoader.initEntryPointGame());
}

void Core::_saveScore() {
	if (this->_moduleLoaded != GAME)
		return;

	std::size_t highScore = this->game->getHighScore();
	std::string username = "default";
	std::string game = this->_gameLibPath.at(this->_gameLibIndex);

	this->_saver.saveScore(highScore, username, game);
}

void Core::_setHighScore() {
	if (this->_moduleLoaded != GAME)
		return;

	std::string username = "default";
	std::string game = this->_gameLibPath.at(this->_gameLibIndex);

	this->game->setHighScore(this->_saver.getHighScore(username, game));
}

void Core::loop() {
	while (this->display->isOpen()) {
		this->_analyze();
		if (this->display->isOpen() == false)
			break;
		this->_compute();
		this->_display();
	}
}
