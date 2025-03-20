/**
 * @file Program.hpp
 * @brief Header file for the Program class.
 *
 * This file contains the declaration of the Program class, which manages
 * three WindowModule objects: Bar, Foo, and Gra.
 *
 * @date 3/17/25
 * @author roussierenoa
 */

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <memory>
#include "WindowModule.hpp"

/**
 * @class Program
 * @brief Manages WindowModule objects.
 *
 * The Program class is responsible for initializing and managing three
 * WindowModule objects: Bar, Foo, and Gra.
 */
class Program {
private:
	Loader::LibLoader _displayLoader; ///< Unique pointer to the DisplayLoader LibLoader.
	// std::unique_ptr<Loader::LibLoader> _gameLoader; ///< Unique pointer to the GameLoader LibLoader.

	std::unique_ptr<WindowModule> display; ///< Unique pointer to the display WindowModule.
	// std::unique_ptr<GameModule> game; ///< Unique pointer to the game GameModule.

public:
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

	/**
	 * @brief Constructs a new Program object.
	 *
	 * The constructor initializes the unique pointers to the DisplayModule objects.
	 */
	Program();

	/**
	 * @brief Destroys the Program object.
	 *
	 * The destructor cleans up the resources used by the Program.
	 */
	~Program();
};

#endif // PROGRAM_HPP

