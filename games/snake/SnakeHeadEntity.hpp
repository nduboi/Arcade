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

class SnakeBodyEntity;

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

        std::vector<std::shared_ptr<SnakeBodyEntity>> findAndSortBodyParts(const grid_t &grid) const;
        void moveBodyPartsToNewPositions(IGameModule &gameModule, const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts);
        void updateBodyPartDirections(IGameModule &gameModule, const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts);
        void addFirstBodyPart(IGameModule &gameModule);
        void addBodyPartToTail(IGameModule &gameModule, size_t index, const std::pair<size_t, size_t> &lastBodyPos, const std::pair<size_t, size_t> &beforeLastPos);
        bool isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const;

    public:
        SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~SnakeHeadEntity() = default;

        gameState_t moveEntity(IGameModule &gameModule, std::pair<int, int> direction) override;
        void addBodyPart(IGameModule &gameModule);
        std::string getSpriteName() const override;
        size_t getBodySize() const;
};

#endif /* !SNAKEHEAD_HPP_ */
