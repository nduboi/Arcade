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
	const int hudOffset = 100; // HUD offset of 100 pixels at the top

	windowPosition.first = (position.first * windowSize.x) / this->_mapSize.first;
	windowPosition.second = hudOffset + (position.second * (windowSize.y - hudOffset)) / this->_mapSize.second;
	return windowPosition;
}

void arcadeSFML::_resizeData(sf::Sprite &sprite, std::pair<int, int> position) {
	sf::Vector2u windowSize = this->window.getSize();
	windowSize.y -= 100;
	sf::Vector2u textureSize = sprite.getTexture()->getSize();
	sf::Vector2u cellSize = {windowSize.x / (int)this->_mapSize.first, windowSize.y / (int)this->_mapSize.second};

	sprite.setScale((float)cellSize.x / textureSize.x + 0.1, (float)cellSize.y / textureSize.y + 0.1);
}

void arcadeSFML::_resizeData(sf::RectangleShape &rectangle, std::pair<int, int> position) {
	sf::Vector2u windowSize = this->window.getSize();
	windowSize.y -= 100;
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

void arcadeSFML::drawRectangleMenu(std::pair<size_t, size_t> size, std::pair<size_t, size_t> position, color_t color)
{
    sf::RectangleShape rectangle(sf::Vector2f(size.first, size.second));
    rectangle.setPosition(position.first, position.second);
    rectangle.setFillColor(sf::Color(color.r, color.g, color.b));
    this->window.draw(rectangle);
}

void arcadeSFML::drawTextMenu(std::string text, std::pair<size_t, size_t> position, color_t color, int charSize)
{
    sf::Font font;
    if (!font.loadFromFile("assets/Arial.ttf"))
        return;

    sf::Text sfText;
    sfText.setFont(font);
    sfText.setString(text);
    sfText.setCharacterSize(charSize);
    sfText.setFillColor(sf::Color(color.r, color.g, color.b));
    sfText.setPosition(position.first, position.second);

    this->window.draw(sfText);
}

void arcadeSFML::drawSpriteMenu(std::pair<float, float> size, std::string asset, std::pair<int, int> position)
{
    sf::Texture texture;
    if (!texture.loadFromFile(asset))
        return;

    sf::Sprite sprite(texture);
    sprite.setPosition(position.first, position.second);
    sprite.setScale(
        size.first / texture.getSize().x,
        size.second / texture.getSize().y
    );

    this->window.draw(sprite);
}

void arcadeSFML::drawThickRectangle(std::pair<int, int> position, std::pair<int, int> size, int thickness)
{
    sf::RectangleShape outerRect(sf::Vector2f(size.first, size.second));
    outerRect.setPosition(position.first, position.second);
    outerRect.setFillColor(sf::Color::White);

    sf::RectangleShape innerRect(sf::Vector2f(
        size.first - 2 * thickness,
        size.second - 2 * thickness
    ));
    innerRect.setPosition(
        position.first + thickness,
        position.second + thickness
    );
    innerRect.setFillColor(sf::Color::Black);

    this->window.draw(outerRect);
    this->window.draw(innerRect);
}

std::pair<int, int> arcadeSFML::getWindowSize() {
	sf::Vector2u size = this->window.getSize();
	return {static_cast<int>(size.x), static_cast<int>(size.y)};
}

bool arcadeSFML::isMouseOver(std::pair<size_t, size_t> position, std::pair<size_t, size_t> size) {
	//TODO: À implémenter
	return false;
}

void arcadeSFML::drawText(std::string text, int color, std::pair<size_t, size_t> position) {
	sf::Text sfText;
	sf::Font font;

	if (!font.loadFromFile("assets/Arial.ttf"))
		return;

	sfText.setFont(font);
	sfText.setString(text);
	sfText.setCharacterSize(24);
	switch (color)
	{
		case 0: sfText.setFillColor(sf::Color::Black); break;
		case 1: sfText.setFillColor(sf::Color::White); break;
		case 2: sfText.setFillColor(sf::Color::Red); break;
		case 3: sfText.setFillColor(sf::Color::Green); break;
		case 4: sfText.setFillColor(sf::Color::Blue); break;
		default: sfText.setFillColor(sf::Color::Black); break;
	}
	sfText.setPosition(position.first, position.second);
	this->window.draw(sfText);
}

void arcadeSFML::setMapSize(std::pair<size_t, size_t> size) {
	this->_mapSize = size;
}

void arcadeSFML::resizeWindow(size_t x, size_t y) {
	this->window.setSize({static_cast<unsigned>(x), static_cast<unsigned>(y)});
}

arcadeSFML::arcadeSFML() :
	window(sf::VideoMode(800, 900), "SFML window", sf::Style::Titlebar | sf::Style::Close)
{
	this->_mapSize = {0, 0};
}
