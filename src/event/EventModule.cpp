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

int EventModule::pollEvents() {
	if (!this->_object)
		throw EventModuleException("No lib loaded");
	return this->_object->pollEvents();
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
