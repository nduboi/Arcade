/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeHead
*/

#ifndef SNAKEHEAD_HPP_
#define SNAKEHEAD_HPP_

#include <map>
#include <chrono>
#include <vector>

#include "AEntity.hpp"

class SnakeHeadEntity : public AEntity {
    private:
        std::chrono::time_point<std::chrono::steady_clock> _lastTime;
        std::pair<int, int> _direction;
        std::map<std::pair<size_t, size_t>, std::string> _assetsName;
        std::vector<std::pair<size_t, size_t>> _previousPositions;

        void setDirection(std::pair<int, int> direction);
        void moveEntities(IGameModule &gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2);
        bool lastTimePassed();
        void moveBodyParts(IGameModule &gameModule);
        bool checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, IGameModule &gameModule) const;

    public:
        SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~SnakeHeadEntity() = default;

        gameState_t moveEntity(IGameModule &gameModule, std::pair<int, int> direction) override;
        void addBodyPart(IGameModule &gameModule);
        std::string getSpriteName() const override;
        size_t getBodySize() const;
};

#endif /* !SNAKEHEAD_HPP_ */
