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
#include "PacmanGame.hpp"

extern "C" {
	IGameModule *createGame(void) {
		return new PacmanGame();
	}
	Loader::ModuleType_t getType(void) {
		return Loader::ModuleType_t::GAME_MODULE;
	}
	__attribute__((constructor)) void construct()
	{
		#ifdef _DEBUG
			std::cout << "Loaded dynamic lib: Lib PACMAN" << std::endl;
		#endif
	}
	__attribute__((destructor)) void deconstruct()
	{
		#ifdef _DEBUG
			std::cout << "Unloaded dynamic lib: Lib PACMAN" << std::endl;
		#endif
	}
}
