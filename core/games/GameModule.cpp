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
	return this->_object->getEntities();
}

void GameModule::setEntities(grid_t entities) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setEntities(entities);
}

std::pair<size_t, size_t> GameModule::getGridSize() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getGridSize();
}

bool GameModule::getIsStarted() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getIsStarted();
}

void GameModule::setIsStarted(bool isStarted) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setIsStarted(isStarted);
}

gameState_t GameModule::getGameState() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getGameState();
}

void GameModule::setGameState(gameState_t gameState) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setGameState(gameState);
}

std::vector<std::shared_ptr<IEntity>> GameModule::getHUD() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getHUD();
}

size_t GameModule::getTime() const {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	return this->_object->getTime();
}

void GameModule::setTime(size_t time) {
	if (!this->_object)
		throw GameModuleException("Error no lib Loaded");
	this->_object->setTime(time);
}

GameModule::GameModule(IGameModule *mdl) {
	this->_object.reset(mdl);
}
