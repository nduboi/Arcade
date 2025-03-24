//
// Created by roussierenoa on 3/24/25.
//
/**
 * @file main.cpp
 * @brief Entry point for the libSDL library.
 *
 * This file contains the implementation of the getClass function which
 * returns an instance of the libSDL class.
 *
 * @author roussierenoa
 * @date 3/17/25
 */

#include <iostream>
#include <unistd.h>
#include "arcadeNcurses.hpp"
#include "arcadeNcursesEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
	IWindow *createInstance(void) {
		return new arcadeNcurses();
	}
	IEvent *createEvent(IWindow &Window) {
		return new arcadeNcursesEvent(Window);
	}
	Loader::ModuleType_t getType(void) {
		return Loader::ModuleType_t::DISPLAY_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
#ifdef _DEBUG
		std::cout << "Loaded dynamic lib: Lib SDL" << std::endl;
#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
#ifdef _DEBUG
		std::cout << "Unloaded dynamic lib: Lib SDL" << std::endl;
#endif
	}
}
