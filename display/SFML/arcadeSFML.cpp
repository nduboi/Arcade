//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include "arcadeSFML.hpp"

void arcadeSFML::initWindow() {
}

void arcadeSFML::display() {
	this->window.display();
}

void arcadeSFML::closeWindow() {
	this->window.close();
}

bool arcadeSFML::isOpen() {
	return this->window.isOpen();
}

void arcadeSFML::clear() {
	this->window.clear();
}

arcadeSFML::arcadeSFML() :
	window(sf::VideoMode(800, 600), "SFML window")
{
}
