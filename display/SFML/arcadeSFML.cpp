//
// Created by roussierenoa on 3/17/25.
//

#include <iostream>
#include "arcadeSFML.hpp"

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

void arcadeSFML::_resizeData(sf::Sprite &sprite, std::pair<int, int> position) {
	sf::Vector2u windowSize = this->window.getSize();
	sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sf::Vector2u cellSize = {windowSize.x / (int)this->_mapSize.first, windowSize.y / (int)this->_mapSize.second};

	sprite.setScale((float)cellSize.x / textureSize.x + 0.1, (float)cellSize.y / textureSize.y + 0.1);
}

void arcadeSFML::_resizeData(sf::RectangleShape &rectangle, std::pair<int, int> position) {
	sf::Vector2u windowSize = this->window.getSize();
	sf::Vector2f rectangleSize = rectangle.getSize();
	sf::Vector2f cellSize = {
		static_cast<float>(windowSize.x) / static_cast<float>(this->_mapSize.first),
		static_cast<float>(windowSize.y) / static_cast<float>(this->_mapSize.second)
	};

	rectangle.setSize({cellSize.x, cellSize.y});
}

void arcadeSFML::drawSprite(std::string asset, int color, std::string text, std::pair<size_t, size_t> position) {
	sf::Texture texture;
	sf::Sprite sprite;
	std::pair<int, int> windowPosition = this->_getWindowPosition(position);

	sf::err().rdbuf(nullptr);
	if (!texture.loadFromFile(asset)) {
		sf::err().rdbuf(std::cerr.rdbuf());
		this->drawRectangle(color, windowPosition);
		return;
	}
	sf::err().rdbuf(std::cerr.rdbuf());
	sprite.setTexture(texture);
	sprite.setPosition(windowPosition.first, windowPosition.second);
	this->_resizeData(sprite, position);
	this->window.draw(sprite);
	(void)text;
}

void arcadeSFML::drawRectangle(int color, std::pair<size_t, size_t> position) {
	sf::RectangleShape rect;

	rect.setPosition(position.first, position.second);
	switch (color)
	{
		case 0: rect.setFillColor(sf::Color::Black); break;
		case 1: rect.setFillColor(sf::Color::White); break;
		case 2: rect.setFillColor(sf::Color::Red); break;
		case 3: rect.setFillColor(sf::Color::Green); break;
		case 4: rect.setFillColor(sf::Color::Blue); break;
		default: rect.setFillColor(sf::Color::Black); break;
	}
	this->_resizeData(rect, position);
	this->window.draw(rect);
}

void arcadeSFML::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position) {
	//TODO: À implémenter
}

void arcadeSFML::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color, color_t outline,  int thickness) {
	//TODO: À implémenter
}

void arcadeSFML::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness) {
	//TODO: À implémenter
}

void arcadeSFML::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color) {
	//TODO: À implémenter
}

std::pair<int, int> arcadeSFML::getWindowSize() {
	//TODO: À implémenter
	return {0, 0};
}

bool arcadeSFML::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
	//TODO: À implémenter
	return false;
}

void arcadeSFML::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
	(void)text;
	(void)color;
	(void)position;
}

void arcadeSFML::setMapSize(std::pair<size_t, size_t> size) {
	this->_mapSize = size;
}

void arcadeSFML::resizeWindow(size_t x, size_t y) {
	this->window.setSize({static_cast<unsigned>(x), static_cast<unsigned>(y)});
}

arcadeSFML::arcadeSFML() :
	window(sf::VideoMode(800, 800), "SFML window", sf::Style::Titlebar | sf::Style::Close)
{
	this->_mapSize = {0, 0};
}
