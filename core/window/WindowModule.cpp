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

WindowModule::WindowModule(IWindow *mdl)
{
	this->_object.reset(mdl);
}

WindowModule::~WindowModule()
{
}
