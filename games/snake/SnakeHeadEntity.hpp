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
        std::pair<int, int> _inputDirection;
        std::pair<int, int> _direction;
        std::map<std::pair<size_t, size_t>, std::string> _assetsName;
        std::vector<std::pair<size_t, size_t>> _previousPositions;
        bool _pendingBodyPartAddition;
        std::pair<size_t, size_t> _lastTailPosition;
        bool _closeToApple;

        void setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule);
        void moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2);
        bool lastTimePassed(std::shared_ptr<IGameModule> gameModule);
        void moveBodyParts(std::shared_ptr<IGameModule> gameModule);
        bool checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const;
        gameState_t appleCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> nextPosition);

        std::vector<std::shared_ptr<SnakeBodyEntity>> findAndSortBodyParts(const grid_t &grid) const;
        void moveBodyPartsToNewPositions(std::shared_ptr<IGameModule> gameModule, const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts);
        void updateBodyPartDirections(std::shared_ptr<IGameModule> gameModule, const std::vector<std::shared_ptr<SnakeBodyEntity>> &bodyParts);
        void addFirstBodyPart(std::shared_ptr<IGameModule> gameModule);
        void addBodyPartToTail(std::shared_ptr<IGameModule> gameModule, size_t index, const std::pair<size_t, size_t> &lastBodyPos, const std::pair<size_t, size_t> &beforeLastPos);
        bool isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const;
        void addPendingBodyPart(std::shared_ptr<IGameModule> gameModule);
        void ensurePreviousPositionsInitialized(std::shared_ptr<IGameModule> gameModule);

        float getSpeedMultiplier(std::shared_ptr<IGameModule> gameModule) const;

        bool isCloseToApple(std::shared_ptr<IGameModule> gameModule) const;

    public:
        SnakeHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~SnakeHeadEntity() = default;

        void moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction) override;
        void addBodyPart(std::shared_ptr<IGameModule> gameModule);
        std::string getSpriteName() const override;
        size_t getBodySize() const;
        void initializePreviousPositions(const std::vector<std::pair<size_t, size_t>>& positions);
};

#endif /* !SNAKEHEAD_HPP_ */
