/**
 * @file WindowModule.hpp
 * @brief Declaration of the WindowModule class.
 *
 * This file contains the definition of the WindowModule class, which implements
 * the IWindowModule interface. It is responsible for managing the display module
 * functionality and interacts with a library loader.
 *
 * @author EPITECH PROJECT
 * @date 2025
 */

#ifndef WindowModule_HPP
#define WindowModule_HPP

#include <memory>
#include "IWindow.hpp"
#include "LibLoader.hpp"
/**
 * @class WindowModule
 * @brief A class that implements the IWindowModule interface.
 *
 * The WindowModule class is responsible for initializing and stopping
 * the display module. It interacts with a library loader to manage
 * dynamic libraries.
 */
class WindowModule : public IWindow{
private:
	std::shared_ptr<IWindow> _object; /**< Reference to the library loader. */

public:
	IWindow *getObject() {return this->_object.get();};

	void display() override;

	void closeWindow() override;
	bool isOpen() override;
	void clear() override;
	void drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) override;
	void drawRectangle(int color, std::pair<size_t, size_t> position) override;
	void drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color) override;
	void drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) override;
	void drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) override;
	void drawText(std::string text, int color, std::pair<size_t, size_t> position) override;
	void drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) override;
	void setMapSize(std::pair<size_t, size_t> size) override;
	std::pair<int, int> getWindowSize() override;
	bool isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) override;
	void resizeWindow(size_t x, size_t y) override;

	/**
	 * @brief Constructor for the WidnowModule class.
	 * 
	 * @param WindowModule A pointer to an object implementing the IWindow interface.
	 *                      This parameter is used to initialize the WidnowModule instance.
	 */
	WindowModule(std::shared_ptr<IWindow>);
	/**
	 * @brief Destructor for the WidnowModule class.
	 */
	~WindowModule() override;

};

#endif // LIBMODULE_HPP
