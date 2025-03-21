//
// Created by roussierenoa on 3/20/25.
//

#include "MenuModule.hpp"
#include "Exception.hpp"

std::size_t MenuModule::getHighScore() const {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	return this->_object->getHighScore();
}

void MenuModule::setHighScore(std::size_t highScore) {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	this->_object->setHighScore(highScore);
}

std::size_t MenuModule::getScore() const {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	return this->_object->getScore();
}

void MenuModule::setScore(std::size_t score) {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	this->_object->setScore(score);
}

grid_t MenuModule::getEntities() const {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	return this->_object->getEntities();
}

std::pair<size_t, size_t> MenuModule::getGridSize() const {
	if (!this->_object)
		throw MenuModuleException("Error no lib Loaded");
	return this->_object->getGridSize();
}

MenuModule::MenuModule(IMenuModule *mdl) {
	this->_object.reset(mdl);
}
