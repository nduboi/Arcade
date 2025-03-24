/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#include "Cell.hpp"

Cell::Cell(size_t x, size_t y)
{
    this->_isRevealed = false;
    this->_isFlagged = false;
    this->_isMine = false;
    this->_adjacentMines = 0;
    this->_position = {x, y};
    this->_spriteName = "./assets/minesweeper/hidden.png";
    this->_color = 0xCCCCCC;
    this->_text = "";
    this->_isMovable = false;
    this->_hasCollisions = false;
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

std::string Cell::getSpriteName() const
{
    if (this->_isFlagged) {
        return "./assets/minesweeper/flag.png";
    } else if (!this->_isRevealed) {
        return "./assets/minesweeper/hidden.png";
    } else if (this->_isMine) {
        return "./assets/minesweeper/mine.png";
    } else {
        return "./assets/minesweeper/cell_" + std::to_string(_adjacentMines) + ".png";
    }
}

std::size_t Cell::getColor() const
{
    if (!this->_isRevealed)
        return 0xCCCCCC;  // Light gray for hide cells
    if (this->_isMine)
        return 0xFF0000;  // Red for mines
    if (this->_adjacentMines == 0)
        return 0xFFFFFF;  // White for empty cells
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

std::string Cell::getText() const
{
    if (this->_isFlagged)
        return "F";
    if (!this->_isRevealed)
        return "";
    if (this->_isMine)
        return "#";
    if (this->_adjacentMines > 0)
        return std::to_string(this->_adjacentMines);
    return "";
}


void Cell::setRevealed(bool revealed)
{
    this->_isRevealed = revealed;
    if (revealed) {
        if (this->_isMine) {
            this->_spriteName = "./assets/minesweeper/mine_reveal.png";
            this->_color = 0xFF0000; // Red for mines
            this->_text = "*";
        } else if (this->_adjacentMines > 0) {
            this->_spriteName = "./assets/minesweeper/cell_" + std::to_string(this->_adjacentMines) + ".png";
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
            this->_color = colors[std::min(this->_adjacentMines, static_cast<size_t>(8)) - 1];
            this->_text = std::to_string(this->_adjacentMines);
        } else {
            this->_spriteName = "./assets/minesweeper/cell_0.png";
            this->_color = 0xFFFFFF; // White for empty cells
            this->_text = "";
        }
    } else {
        this->_spriteName = "./assets/minesweeper/hidden.png";
        this->_color = 0xCCCCCC; // Light gray for hide cells
        this->_text = "";
    }
}

bool Cell::isRevealed() const
{
    return this->_isRevealed;
}

void Cell::setFlagged(bool flagged)
{
    this->_isFlagged = flagged;
    if (flagged) {
        this->_spriteName = "./assets/minesweeper/flag.png";
        this->_text = "F";
    } else if (!_isRevealed) {
        this->_spriteName = "./assets/minesweeper/hidden.png";
        this->_text = "";
    }
}

bool Cell::isFlagged() const
{
    return this->_isFlagged;
}

void Cell::setMine(bool mine)
{
    this->_isMine = mine;
}

bool Cell::isMine() const
{
    return this->_isMine;
}

void Cell::setAdjacentMines(size_t count)
{
    this->_adjacentMines = count;
}

size_t Cell::getAdjacentMines() const
{
    return this->_adjacentMines;
}
