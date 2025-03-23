//
// Created by roussierenoa on 3/17/25.
//

#include <filesystem>
#include <iostream>
#include <vector>
#include "Core.hpp"

#include <cstring>

Core::Core() {
	this->_refreshLibList();
	this->_lastEvent = IEvent::event_t::NOTHING;
}

Core::~Core() {
}

void Core::_analyze() {
	std::pair<size_t, size_t> gridSize {};

	gridSize = this->game->getGridSize();
	IEvent::event_t event = this->event->pollEvents(gridSize);
	this->_lastEvent = IEvent::event_t::NOTHING;

	if (event == IEvent::event_t::LEFT) {
#ifdef _DEBUG
		printf("EVENT LEFT\n");
#endif
	}
	if (event == IEvent::event_t::RIGHT) {
#ifdef _DEBUG
		printf("EVENT RIGHT\n");
#endif
	}
	if (event == IEvent::event_t::UP) {
#ifdef _DEBUG
		printf("EVENT UP\n");
#endif
	}
	if (event == IEvent::event_t::DOWN) {
#ifdef _DEBUG
		printf("EVENT DOWN\n");
#endif
	}
	if (event == IEvent::event_t::MOUSECLICK) {
#ifdef _DEBUG
		printf("EVENT MOUSECLICK\n");
#endif
	}
	if (event == IEvent::event_t::MOUSELEFTCLICK) {
#ifdef _DEBUG
		printf("EVENT MOUSELEFTCLICK\n");
#endif
	}
	if (event == IEvent::event_t::MOUSERIGHTCLICK) {
#ifdef _DEBUG
		printf("EVENT MOUSERIGHTCLICK\n");
#endif
	}
	if (event == IEvent::event_t::NEXTGRAPHIC) {
#ifdef _DEBUG
		printf("EVENT NEXTGRAPHIC\n");
#endif
		this->_loadNextGraphic();
	}
	if (event == IEvent::event_t::CLOSE) {
#ifdef _DEBUG
		printf("EVENT CLOSE\n");
#endif
		this->display->closeWindow();
	}
	if (event == IEvent::event_t::REFRESH) {
#ifdef _DEBUG
		printf("EVENT REFRESH\n");
#endif
		this->_refreshLibList();
	}
	if (event == IEvent::event_t::NEXTGAME) {
#ifdef _DEBUG
		printf("EVENT NEXTGAME\n");
#endif
		this->_loadNextGame();
	}
	if (event == IEvent::event_t::MENU) {
#ifdef _DEBUG
		printf("EVENT MENU\n");
#endif
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
	grid_t grid = this->game->getEntities();
	std::pair<size_t, size_t> gridSize = this->game->getGridSize();

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

void Core::_display() {
	this->display->clear();
	this->_displayGame();
	this->display->display();

}

void Core::_displayGame() {
	grid_t grid = this->game->getEntities();
	std::pair<size_t, size_t> gridSize = this->game->getGridSize();

	this->display->setMapSize({static_cast<int>(gridSize.second), static_cast<int>(gridSize.first)});
	for (int y = 0; y < gridSize.first; y++) {
		for (int x = 0; x < gridSize.second; x++) {
			for (int z = 0; z < grid[y][x].size(); z++) {
				IEntity *entity = grid[y][x][z].get();

				this->display->drawSprite(entity->getSpriteName(), entity->getColor(), {x, y});
				this->display->drawText(entity->getText(), entity->getColor(), {x, y});
			}
		}
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
	if (this->_gameLibPath.size() == 1)
		return;
	this->_gameLibIndex++;
	if (this->_gameLibIndex >= this->_gameLibPath.size())
		this->_gameLibIndex = 0;
	if (strcmp(this->_gameLoader.getModulePath(), "") != 0 && std::filesystem::canonical(this->_gameLibPath.at(this->_gameLibIndex)) == std::filesystem::canonical(this->_gameLoader.getModulePath()))
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
	this->event.reset();
	this->display.reset();
	this->_displayLoader.closeLib();
	sleep(1);
	this->_displayLoader.openLib(path);
	if (this->_displayLoader.getModuleType() != Loader::DISPLAY_MODULE)
		throw CoreException("Error the library loaded is not a Display Module");
	this->display = std::make_unique<WindowModule>(this->_displayLoader.initEntryPointDisplay());
	auto &displayObject = this->display->getObject();
	this->event = std::make_unique<EventModule>(this->_displayLoader.initEntryPointEvent(displayObject));
	this->display->initWindow();
	this->event->init();
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
	while (this->display->isOpen()) {
		this->_analyze();
		if (this->display->isOpen() == false)
			break;
		this->_compute();
		this->_display();
	}
}
