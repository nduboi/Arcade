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

void arcadeSFML::drawSprite(std::string asset, int color, std::pair<int, int> position) {
	(void)asset;
	(void)color;
	(void)position;
}

void arcadeSFML::drawRectangle(int color, std::pair<int, int> position) {
	(void)color;
	(void)position;
}

void arcadeSFML::drawText(std::string text, int color, std::pair<int, int> position) {
	(void)text;
	(void)color;
	(void)position;
}

void arcadeSFML::setMapSize(std::pair<int, int> size) {
	this->_mapSize = size;
}

arcadeSFML::arcadeSFML() :
	window(sf::VideoMode(800, 600), "SFML window")
{
	this->_mapSize = {0, 0};
}
