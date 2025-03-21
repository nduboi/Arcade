//
// Created by roussierenoa on 3/17/25.
//

#include <filesystem>
#include <iostream>
#include <vector>
#include "Core.hpp"

Core::Core() {
	this->_refreshLibList();
}

Core::~Core() {
}

void Core::_analyze() {
	IEvent::event_t event;
	while ((event = this->event->pollEvents({})) != IEvent::event_t::NOTHING) {
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
	}
}

void Core::_compute() {

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

void Core::loadMenuModule(const std::string &path) {
	this->menu.reset();
	this->_menuLoader.closeLib();
	this->_menuLoader.openLib(path.c_str());
	if (this->_menuLoader.getModuleType() != Loader::MENU_MODULE)
		throw CoreException("Error the library loaded is not a Menu Module");
	this->menu = std::make_unique<MenuModule>(this->_menuLoader.initEntryPointMenu());
}

void Core::loop() {
	this->display->initWindow();
	this->event->init();

	while (this->display->isOpen()) {
		this->display->clear();
		this->_analyze();
		this->_compute();

		this->display->display();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
