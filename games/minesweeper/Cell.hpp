/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** Cell
*/

#ifndef CELL_HPP_
#define CELL_HPP_

#include "IEntity.hpp"

class Cell : public IEntity {
    public:
        // Constructor
        Cell(size_t x, size_t y);
        ~Cell() = default;

        // Method
        gameState_t onClick(grid_t &grid, clickType_t type) override;
        gameState_t moveEntity(grid_t &grid) override;
        gameState_t moveEntity(grid_t &grid, std::pair<size_t, size_t> direction) override;
        gameState_t onInteract(grid_t &grid) override;
        bool isMovable() const override;
        bool hasCollisions() const override;
        bool isRevealed() const;
        bool isFlagged() const;
        bool isMine() const;

        // Getter
        std::pair<size_t, size_t> getPosition() const override;
        std::string getSpriteName() const override;
        std::size_t getColor() const override;
        std::string getText() const override;
        size_t getAdjacentMines() const;

        // Setter
        void setPosition(std::pair<size_t, size_t> position) override;
        void setRevealed(bool revealed);
        void setFlagged(bool flagged);
        void setMine(bool mine);
        void setAdjacentMines(size_t count);

    protected:

    private:
        // Variable
        std::pair<size_t, size_t> _position;
        bool _isRevealed;
        bool _isFlagged;
        bool _isMine;
        size_t _adjacentMines;

};

#endif /* !CELL_HPP_ */
