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

std::pair<int, int> arcadeSFML::_getWindowPosition(std::pair<int, int> position) {
	std::pair<int, int> windowPosition;
	sf::Vector2u windowSize = this->window.getSize();

	windowPosition.first = (position.first * windowSize.x) / this->_mapSize.first;
	windowPosition.second = (position.second * windowSize.y) / this->_mapSize.second;
	return windowPosition;
}

void arcadeSFML::_resizeSprite(sf::Sprite &sprite, std::pair<int, int> position) {
	sf::Vector2u windowSize = this->window.getSize();
	sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sf::Vector2u cellSize = {windowSize.x / this->_mapSize.first, windowSize.y / this->_mapSize.second};

	sprite.setScale((float)cellSize.x / textureSize.x + 0.1, (float)cellSize.y / textureSize.y + 0.1);
}

void arcadeSFML::drawSprite(std::string asset, int color, std::pair<size_t, size_t> position) {
	sf::Texture texture;
	sf::Sprite sprite;
	std::pair<int, int> windowPosition = this->_getWindowPosition(position);

	if (!texture.loadFromFile(asset))
		std::cerr << "Error loading texture" << std::endl;
	sprite.setTexture(texture);
	sprite.setPosition(windowPosition.first, windowPosition.second);
	this->_resizeSprite(sprite, position);
	this->window.draw(sprite);
}

void arcadeSFML::drawRectangle(int color, std::pair<size_t, size_t> position) {
	(void)color;
	(void)position;
}

void arcadeSFML::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
	(void)text;
	(void)color;
	(void)position;
}

void arcadeSFML::setMapSize(std::pair<int, int> size) {
	this->_mapSize = size;
}

arcadeSFML::arcadeSFML() :
	window(sf::VideoMode(800, 800), "SFML window", sf::Style::Titlebar | sf::Style::Close)
{
	this->_mapSize = {0, 0};
}
