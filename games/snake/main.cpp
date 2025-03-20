/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** main
*/

#include <iostream>
#include <unistd.h>
#include "LoaderType.hpp"
#include "IGameModule.hpp"
#include "SnakeGame.hpp"

extern "C" {
	IGameModule *getInstanceGame(void) {
		return new SnakeGame();
	}
	Loader::ModuleType_t getModuleType(void) {
		return Loader::ModuleType_t::GAME_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
		#ifdef _DEBUG
			std::cout << "Loaded dynamic lib: Lib SNAKE" << std::endl;
		#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
		#ifdef _DEBUG
			std::cout << "Unloaded dynamic lib: Lib SNAKE" << std::endl;
		#endif
	}
}
