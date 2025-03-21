//
// Created by roussierenoa on 3/17/25.
//

#include <filesystem>
#include <iostream>
#include <vector>
#include "Core.hpp"

Core::Core() {
	this->_refreshLibList();
	this->_lastEvent = IEvent::event_t::NOTHING;
}

Core::~Core() {
}

void Core::_analyze() {
	std::pair<size_t, size_t> gridSize = this->game.get()->getGridSize();
	IEvent::event_t event = this->event->pollEvents(gridSize);
	this->_lastEvent = IEvent::event_t::NOTHING;

	if (event == IEvent::event_t::CLOSE)
		this->display->closeWindow();
	if (event == IEvent::event_t::LEFT)
		printf("EVENT LEFT\n");
	if (event == IEvent::event_t::RIGHT)
		printf("EVENT RIGHT\n");
	if (event == IEvent::event_t::UP)
		printf("EVENT UP\n");
	if (event == IEvent::event_t::DOWN)
		printf("EVENT DOWN\n");
	if (event == IEvent::event_t::NEXTGRAPHIC) {
		printf("EVENT NEXTGRAPHIC\n");
		this->_loadNextGraphic();
	}
	if (event == IEvent::event_t::REFRESH) {
		printf("EVENT REFRESH\n");
		this->_refreshLibList();
	}
	if (event == IEvent::event_t::NEXTGAME) {
		printf("EVENT NEXTGAME\n");
		this->_loadNextGame();
	}
	if (event == IEvent::event_t::MENU) {
		printf("EVENT MENU\n");
		this->loadGameModule("./lib/arcade_menu.so");
	}
	this->_lastEvent = event;
}

std::pair<int, int> Core::_getEventDirection() const {
	std::pair<int, int> direction = {0, 0};

	if (this->_lastEvent == IEvent::event_t::UP)
		direction = {0, 1};
	if (this->_lastEvent == IEvent::event_t::DOWN)
		direction = {0, -1};
	if (this->_lastEvent == IEvent::event_t::LEFT)
		direction = {-1, 0};
	if (this->_lastEvent == IEvent::event_t::RIGHT)
		direction = {1, 0};
	return direction;
}

void Core::_compute() {
	grid_t grid = this->game.get()->getEntities();
	std::pair<size_t, size_t> gridSize = this->game.get()->getGridSize();

	for (int y = 0; y < gridSize.first; y++) {
		for (int x = 0; x < gridSize.second; x++) {
			for (int z = 0; z < grid[y][x].size(); z++) {
				IEntity *entity = grid[y][x][z].get();

				if (entity->isMovable()) {
					if (entity->isControlable()) {
						entity->moveEntity(grid, this->_getEventDirection());
					} else {
						entity->moveEntity(grid);
					}
				}
			}
		}
	}
}

void Core::_computeDisplay() {
	grid_t grid = this->game.get()->getEntities();
	std::pair<size_t, size_t> gridSize = this->game.get()->getGridSize();

	this->display.get()->setMapSize({static_cast<int>(gridSize.second), static_cast<int>(gridSize.first)});
	for (int y = 0; y < gridSize.first; y++) {
		for (int x = 0; x < gridSize.second; x++) {
			for (int z = 0; z < grid[y][x].size(); z++) {
				IEntity *entity = grid[y][x][z].get();

				this->display->drawSprite(entity->getSpriteName(), entity->getColor(), {x, y});
			}
		}
	}
	this->display->display();
}

void Core::_refreshLibList() {
	const std::string libFolder = "./lib";
	Loader::LibLoader libLoader;

	this->_gameLibIndex = 0;
	this->_displayLibIndex = 0;
	try {
		for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
			if (entry.path().extension() == ".so") {
				libLoader.openLib(entry.path().string());
				if (libLoader.getModuleType() == Loader::GAME_MODULE)
					this->_gameLibPath.push_back(entry.path().string());
				else
					this->_displayLibPath.push_back(entry.path().string());
				libLoader.closeLib();
			}
		}
	} catch (const std::filesystem::filesystem_error &e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
	}
}

void Core::_loadNextGame() {
	if (this->_gameLibPath.size() == 1)
		return;
	this->_gameLibIndex++;
	if (this->_gameLibIndex >= this->_gameLibPath.size())
		this->_gameLibIndex = 0;
	if (std::filesystem::canonical(this->_gameLibPath.at(this->_gameLibIndex)) == std::filesystem::canonical(this->_gameLoader.getModulePath()))
		return this->_loadNextGame();
	this->loadGameModule(this->_gameLibPath.at(this->_gameLibIndex));
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
}

void Core::_waitDisplayReady() const {
	while (this->_displayStatus != READY && this->_displayStatus != ERROR);
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
	this->display.reset();
	this->event.reset();
	this->_displayLoader.closeLib();
	this->_displayLoader.openLib(path);
	if (this->_displayLoader.getModuleType() != Loader::DISPLAY_MODULE)
		throw CoreException("Error the library loaded is not a Display Module");
	this->display = std::make_unique<WindowModule>(this->_displayLoader.initEntryPointDisplay());
	auto &displayObject = this->display->getObject();
	this->event = std::make_unique<EventModule>(this->_displayLoader.initEntryPointEvent(displayObject));
}

void Core::loadGameModule(const std::string &path) {
	this->game.reset();
	this->_gameLoader.closeLib();
	this->_gameLoader.openLib(path.c_str());
	if (this->_gameLoader.getModuleType() != Loader::GAME_MODULE)
		throw CoreException("Error the library loaded is not a Game Module");
	this->game = std::make_unique<GameModule>(this->_gameLoader.initEntryPointGame());
}

void Core::loop() {
	this->display->initWindow();
	this->event->init();

	while (this->display->isOpen()) {
		this->display->clear();
		this->_analyze();
		this->_compute();

		this->_computeDisplay();
	}
}
