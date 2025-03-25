//
// Created by roussierenoa on 3/20/25.
//

#include "IGameModule.hpp"
#include "LoaderType.hpp"
#include "Menu.hpp"

extern "C" {
	IMenu *createMenu(void) {
		return new Menu();
	}
	Loader::ModuleType_t getType(void) {
		return Loader::ModuleType_t::MENU_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
#ifdef _DEBUG
		std::cout << "Loaded dynamic lib: Lib MENU" << std::endl;
#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
#ifdef _DEBUG
		std::cout << "Unloaded dynamic lib: Lib MENU" << std::endl;
#endif
	}
}
