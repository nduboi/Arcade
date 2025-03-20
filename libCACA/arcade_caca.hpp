/**
 * @file arcadeCaca.hpp
 * @brief Header file for the arcadeCaca class.
 *
 * This file contains the declaration of the arcadeCaca class, which implements the IDisplayModule interface.
 * 
 * @author roussierenoa
 * @date 3/17/25
 */

#ifndef arcadeCaca_HPP
#define arcadeCaca_HPP

#include "IWindow.hpp"
#include <string>

/**
 * @class arcadeCaca
 * @brief A class that implements the IDisplayModule interface.
 *
 * The arcadeCaca class provides an implementation of the IDisplayModule interface, 
 * including methods for initialization, stopping, and retrieving the module name.
 */
class arcadeCaca : public IWindow {
	std::string _libName = "Arcade Caca"; ///< The name of the library.

public:
	void initWindow() override;

	void display() override;

	void closeWindow() override;

	bool isOpen() override;

	void clear() override;

	arcadeCaca();

	~arcadeCaca() = default;
};

#endif // arcadeCaca_HPP
