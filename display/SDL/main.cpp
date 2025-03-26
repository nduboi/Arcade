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

 /**
	* @brief Factory function to create an instance of libSDL.
	*
	* This function is used to create and return a new instance of the libSDL class.
	* It is intended to be used as an entry point for dynamic loading of the library.
	*
	* @return IDisplayModule* Pointer to the newly created libSDL instance.
	*/
//
// Created by eliotttesnier on 3/21/25.
//

#include <iostream>
#include <unistd.h>
#include "arcadeSDL.hpp"
#include "arcadeSDLEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
	IWindow *createInstance(void) {
		return new arcadeSDL();
	}
	IEvent *createEvent(std::shared_ptr<IWindow> Window) {
		return new arcadeSDLEvent(Window);
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
