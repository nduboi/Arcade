/**
 * @file WindowModule.cpp
 * @brief Implementation of the WindowModule class.
 *
 * This file contains the implementation of the WindowModule class, which
 * provides methods for managing the display window and rendering graphics.
 */

//
// Created by roussierenoa on 3/17/25.
//

#include "WindowModule.hpp"
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

void WindowModule::display() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->display();
}

void WindowModule::closeWindow() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->closeWindow();
}

bool WindowModule::isOpen() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	return this->_object->isOpen();
}

void WindowModule::clear() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->clear();
}

void WindowModule::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawSprite(asset, color, text, position);
}

void WindowModule::drawRectangle(int color, std::pair<size_t, size_t> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawRectangle(color, position);
}

void WindowModule::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position,
	color_t color)
{
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawRectangleMenu(size, position, color);
}

void WindowModule::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawSpriteMenu(size, asset, position);
}

void WindowModule::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawThickRectangle(position, size, thickness);
}

void WindowModule::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawTextMenu(text, position, color, charSize);
}

std::pair<int, int> WindowModule::getWindowSize() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	return this->_object->getWindowSize();
}

bool WindowModule::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	return this->_object->isMouseOver(position, size);
}

void WindowModule::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawText(text, color, position);
}

void WindowModule::setMapSize(std::pair<size_t, size_t> size) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->setMapSize(size);
}

void WindowModule::resizeWindow(size_t x, size_t y) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->resizeWindow(x, y);
}

WindowModule::WindowModule(std::shared_ptr<IWindow> mdl)
{
	this->_object = mdl;
}

WindowModule::~WindowModule()
{
	this->_object.reset();
}

