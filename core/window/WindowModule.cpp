//
// Created by roussierenoa on 3/17/25.
//

#include "WindowModule.hpp"
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

void WindowModule::initWindow() {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->initWindow();
}

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

void WindowModule::drawSprite(std::string asset, int color, std::pair<int, int> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawSprite(asset, color, position);
}

void WindowModule::drawRectangle(int color, std::pair<int, int> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawRectangle(color, position);
}

void WindowModule::drawText(std::string text, int color, std::pair<int, int> position) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->drawText(text, color, position);
}

void WindowModule::setMapSize(std::pair<int, int> size) {
	if (!this->_object)
		throw WindowException("Error no lib Loaded");
	this->_object->setMapSize(size);
}

WindowModule::WindowModule(IWindow *mdl)
{
	this->_object.reset(mdl);
}

WindowModule::~WindowModule()
{
	this->_object.reset();
}
