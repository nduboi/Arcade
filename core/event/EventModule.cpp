//
// Created by roussierenoa on 3/17/25.
//

#include "EventModule.hpp"
#include <dlfcn.h>
#include <iostream>
#include <stdexcept>

void EventModule::init() {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	this->_object->init();
}

IEvent::event_t EventModule::pollEvents(std::pair<int, int> gridSize) {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	return this->_object->pollEvents(gridSize);
}

std::pair<int, int> EventModule::getMousePos() {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	return this->_object->getMousePos();
}

void EventModule::setMapSize(std::pair<int, int> size) {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	this->_object->setMapSize(size);
}

void EventModule::cleanup() {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	this->_object->cleanup();
}

EventModule::EventModule(IEvent *mdl)
{
	this->_object.reset(mdl);
}

EventModule::~EventModule()
{
}
