/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#include "Cell.hpp"

Cell::Cell(size_t x, size_t y)
{
    _isRevealed = false;
    _isFlagged = false;
    _isMine = false;
    _adjacentMines = 0;
    _position = {x, y};
    _spriteName = "hidden.png";
    _color = 0xCCCCCC;
    _text = "";
    _isMovable = false;
    _hasCollisions = false;
}

gameState_t Cell::onClick(grid_t &grid, clickType_t type)
{
    if (type == LEFT_CLICK) {
        return PLAYING;
    } else if (type == RIGHT_CLICK) {
        return PLAYING;
    }
    return PLAYING;
}

gameState_t Cell::onInteract(grid_t &grid)
{
    return onClick(grid, LEFT_CLICK);
}

std::string Cell::getSpriteName() const
{
    if (_isFlagged) {
        return "flag.png";
    } else if (!_isRevealed) {
        return "hidden.png";
    } else if (_isMine) {
        return "mine.png";
    } else {
        return "cell_" + std::to_string(_adjacentMines) + ".png";
    }
}

std::size_t Cell::getColor() const
{
    if (!_isRevealed) {
        return 0xCCCCCC;  // Light gray for hide cells
    } else if (_isMine) {
        return 0xFF0000;  // Red for mines
    } else if (_adjacentMines == 0) {
        return 0xFFFFFF;  // White for empty cells
    } else {
        static const std::size_t colors[] = {
            0x0000FF,  // 1: Blue
            0x008000,  // 2: Green
            0xFA8072,  // 3: Light red
            0x000080,  // 4: Dark blue
            0x800000,  // 5: Brown
            0x008080,  // 6: Cyan
            0x000000,  // 7: Black
            0x808080   // 8: Grey
        };
        return colors[std::min(_adjacentMines, static_cast<size_t>(8)) - 1];
    }
}

std::string Cell::getText() const
{
    if (_isFlagged) {
        return "F";
    } else if (!_isRevealed) {
        return "";
    } else if (_isMine) {
        return "#";
    } else if (_adjacentMines > 0) {
        return std::to_string(_adjacentMines);
    } else {
        return "";
    }
}


void Cell::setRevealed(bool revealed)
{
    _isRevealed = revealed;
    if (revealed) {
        if (_isMine) {
            _spriteName = "mine_reveal.png";
            _color = 0xFF0000; // Red for mines
            _text = "*";
        } else if (_adjacentMines > 0) {
            _spriteName = "cell_" + std::to_string(_adjacentMines) + ".png";
            static const std::size_t colors[] = {
                0x0000FF,  // 1: Blue
                0x008000,  // 2: Green
                0xFA8072,  // 3: Light red
                0x000080,  // 4: Dark blue
                0x800000,  // 5: Brown
                0x008080,  // 6: Cyan
                0x000000,  // 7: Black
                0x808080   // 8: Grey
            };
            _color = colors[std::min(_adjacentMines, static_cast<size_t>(8)) - 1];
            _text = std::to_string(_adjacentMines);
        } else {
            _spriteName = "cell_0.png";
            _color = 0xFFFFFF; // White for empty cells
            _text = "";
        }
    } else {
        _spriteName = "hidden.png";
        _color = 0xCCCCCC; // Light gray for hide cells
        _text = "";
    }
}

bool Cell::isRevealed() const
{
    return _isRevealed;
}

void Cell::setFlagged(bool flagged)
{
    _isFlagged = flagged;
    if (flagged) {
        _spriteName = "flag.png";
        _text = "F";
    } else if (!_isRevealed) {
        _spriteName = "hidden.png";
        _text = "";
    }
}

bool Cell::isFlagged() const
{
    return _isFlagged;
}

void Cell::setMine(bool mine)
{
    _isMine = mine;
}

bool Cell::isMine() const
{
    return _isMine;
}

void Cell::setAdjacentMines(size_t count)
{
    _adjacentMines = count;
}

size_t Cell::getAdjacentMines() const
{
    return _adjacentMines;
}
