//
// Created by roussierenoa on 3/17/25.
//

#include <filesystem>
#include <iostream>
#include <vector>
#include "Program.hpp"

Program::Program() {}

Program::~Program() {
}

void Program::displayAllLib()
{
	const std::string libFolder = "./lib";
	Loader::LibLoader libLoader;
	std::vector<std::string> display;
	std::vector<std::string> game;

	try {
		for (const auto &entry : std::filesystem::directory_iterator(libFolder)) {
			if (entry.path().extension() == ".so") {
				libLoader.openLib(entry.path().string());
				if (libLoader.getModuleType() == Loader::GAME_MODULE)
					game.push_back(entry.path().string());
				else
					display.push_back(entry.path().string());
				libLoader.closeLib();
			}
		}
	} catch (const std::filesystem::filesystem_error &e) {
		std::cerr << "Error accessing directory: " << e.what() << std::endl;
	}
	std::cout << "Display lib:" << std::endl;
	for (auto s: display)
		std::cout << "  " << s << std::endl;

	std::cout << std::endl;
	std::cout << "Game lib:" << std::endl;
	for (auto s: game)
		std::cout << "  " << s << std::endl;
}

void Program::loadDisplayModule(const std::string &path)
{
	this->display.reset();
	this->_displayLoader.closeLib();
	this->_displayLoader.openLib(path);
	if (this->_displayLoader.getModuleType() != Loader::DISPLAY_MODULE) {
		throw ProgramCoreException("Error the library loaded is not a Display Module");
	}
	this->display = std::make_unique<WindowModule>(this->_displayLoader.initEntryPointDisplay());
	this->event = std::make_unique<EventModule>(this->_displayLoader.initEntryPointEvent(*this->display));
}
