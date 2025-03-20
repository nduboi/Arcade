/**
 * @file main.cpp
 * @brief Entry point for the libGra library.
 *
 * This file contains the implementation of the getClass function which
 * returns an instance of the libGra class.
 *
 * @author roussierenoa
 * @date 3/17/25
 */

 /**
	* @brief Factory function to create an instance of libGra.
	*
	* This function is used to create and return a new instance of the libGra class.
	* It is intended to be used as an entry point for dynamic loading of the library.
	*
	* @return IDisplayModule* Pointer to the newly created libGra instance.
	*/
//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include <unistd.h>
#include "arcadeCaca.hpp"
#include "arcadeCacaEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
	IWindow *createInstance(void) {
		return new arcadeCaca;
	}
	IEvent *createEvent(IWindow &Window) {
		return new arcadeCacaEvent(Window);
	}
	Loader::ModuleType_t getType(void) {
		return Loader::ModuleType_t::DISPLAY_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
		#ifdef _DEBUG
			std::cout << "Loaded dynamic lib: Lib CACA" << std::endl;
		#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
		#ifdef _DEBUG
			std::cout << "Unloaded dynamic lib: Lib CACA" << std::endl;
		#endif
	}
}