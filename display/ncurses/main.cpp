//
// Created by noaroussiere on 3/21/25.
//

#include <iostream>
#include <unistd.h>
#include "arcadeNcurses.hpp"
#include "arcadeNcursesEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
	IWindow *createInstance(void) {
		return new DisplayLib::arcadeNcurses();
	}
	IEvent *createEvent(std::shared_ptr<IWindow> Window) {
		return new DisplayLib::arcadeNcursesEvent(Window);
	}
	Loader::ModuleType_t getType(void) {
		return Loader::ModuleType_t::DISPLAY_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
#ifdef _DEBUG
		std::cout << "Loaded dynamic lib: Lib NCURSES" << std::endl;
#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
#ifdef _DEBUG
		std::cout << "Unloaded dynamic lib: Lib NCURSES" << std::endl;
#endif
	}
}
