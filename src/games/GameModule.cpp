//
// Created by roussierenoa on 3/20/25.
//

#include "GameModule.hpp"
#include "Exception.hpp"

std::size_t GameModule::getHighScore() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getHighScore();
}

void GameModule::setHighScore(std::size_t highScore) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setHighScore(highScore);
}

std::size_t GameModule::getScore() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getScore();
}

void GameModule::setScore(std::size_t score) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setScore(score);
}

grid_t GameModule::getEntities() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return grid_t {};
}

std::pair<size_t, size_t> GameModule::getGridSize() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getGridSize();
}
