//
// Created by roussierenoa on 3/20/25.
//

#include "MenuModule.hpp"
#include "Exception.hpp"

std::vector<Boxes> MenuModule::getBoxPoses(std::shared_ptr<IWindow> window) {
	if (!this->_object) {
		throw MenuModuleException("Module not loaded");
	}
	return this->_object->getBoxPoses(window);
}

std::string MenuModule::getUsername()
{
	if (!this->_object) {
		throw MenuModuleException("Module not loaded");
	}
	return this->_object->getUsername();
}

void MenuModule::setUsername(std::string username) {
	if (!this->_object) {
		throw MenuModuleException("Module not loaded");
	}
	this->_object->setUsername(username);
}

void MenuModule::displayMenu(std::shared_ptr<IWindow> window, std::vector<Boxes> _boxes, std::vector<std::string> libs,
	std::vector<std::string> games)
{
	if (!this->_object) {
		throw MenuModuleException("Module not loaded");
	}
	this->_object->displayMenu(window, _boxes, libs, games);
}

MenuModule::MenuModule(IMenu *mdl) {
	this->_object.reset(mdl);
}
