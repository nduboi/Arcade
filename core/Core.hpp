/**
 * @file Core.hpp
 * @brief Header file for the Core class.
 *
 * This file contains the declaration of the Core class, which manages
 * three WindowModule objects: Bar, Foo, and Gra.
 *
 * @date 3/17/25
 * @author roussierenoa
 */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <memory>
#include "EventModule.hpp"
#include "WindowModule.hpp"
#include "GameModule.hpp"

/**
 * @class Core
 * @brief Manages WindowModule objects.
 *
 * The Core class is responsible for initializing and managing three
 * WindowModule objects: Bar, Foo, and Gra.
 */
class Core {
private:
	Loader::LibLoader _displayLoader; ///< Unique pointer to the DisplayLoader LibLoader.
	Loader::LibLoader _gameLoader; ///< Unique pointer to the GameLoader LibLoader.

public:
	std::unique_ptr<WindowModule> display; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<EventModule> event; ///< Unique pointer to the display WindowModule.
	std::unique_ptr<GameModule> game; ///< Unique pointer to the game GameModule.
	// std::unique_ptr<Enti>
	/**
	 * @brief Display All lib.
	 *
	 * This function permit to display all lib availables
	 */
	void displayAllLib();

	/**
	 * @brief Load a display module.
	 *
	 * This function permit to load a display Module
	 */
	void loadDisplayModule(const std::string &displayLib);

	void loadGameModule(const std::string &gameLib);

	/**
	 * @brief Constructs a new Core object.
	 *
	 * The constructor initializes the unique pointers to the DisplayModule objects.
	 */
	Core();

	/**
	 * @brief Destroys the Core object.
	 *
	 * The destructor cleans up the resources used by the Core.
	 */
	~Core();
};

#endif // PROGRAM_HPP

