/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerHeadEntity
*/

#ifndef NIBBLERHEADENTITY_HPP_
#define NIBBLERHEADENTITY_HPP_

#include <map>
#include <chrono>
#include <vector>

#include "AEntity.hpp"

class NibblerTailEntity;

class NibblerHeadEntity : public AEntity {
    public:
        // Constructor
        NibblerHeadEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position);
        ~NibblerHeadEntity() = default;

        // Method
        void moveEntity(std::shared_ptr<IGameModule> gameModule, std::pair<int, int> direction) override;
        void addBodyPart(std::shared_ptr<IGameModule> gameModule);
        void initializePreviousPositions(const std::vector<std::pair<size_t, size_t>>& positions);

        // Getter
        std::string getSpriteName() const override;
        size_t getBodySize() const;

    private:
        // Variable
        std::chrono::time_point<std::chrono::steady_clock> _lastTime;
        std::chrono::time_point<std::chrono::steady_clock> _pauseUntil;
        bool _isPaused;
        std::pair<int, int> _inputDirection;
        std::pair<int, int> _direction;
        std::map<std::pair<int, int>, std::string> _assetsName;
        std::vector<std::pair<size_t, size_t>> _previousPositions;
        bool _pendingBodyPartAddition;
        std::pair<size_t, size_t> _lastTailPosition;

        // Setter
        void setDirection(std::pair<int, int> direction, std::shared_ptr<IGameModule> gameModule);

        // Method
        void moveEntities(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> pos1, std::pair<size_t, size_t> pos2);
        bool lastTimePassed();
        bool isAtIntersection(std::shared_ptr<IGameModule> gameModule);
        void moveBodyParts(std::shared_ptr<IGameModule> gameModule);
        bool checkCollisionWithBody(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const;
        bool checkCollisionWithWall(std::pair<size_t, size_t> nextPosition, std::shared_ptr<IGameModule> gameModule) const;
        gameState_t foodCollision(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> nextPosition);

        std::vector<std::shared_ptr<NibblerTailEntity>> findAndSortBodyParts(const grid_t &grid) const;
        void moveBodyPartsToNewPositions(std::shared_ptr<IGameModule> gameModule, const std::vector<std::shared_ptr<NibblerTailEntity>> &bodyParts);
        void updateBodyPartDirections(std::shared_ptr<IGameModule> gameModule, const std::vector<std::shared_ptr<NibblerTailEntity>> &bodyParts);
        void addFirstBodyPart(std::shared_ptr<IGameModule> gameModule);
        void addBodyPartToTail(std::shared_ptr<IGameModule> gameModule, size_t index, const std::pair<size_t, size_t> &lastBodyPos, const std::pair<size_t, size_t> &beforeLastPos);
        bool isValidPosition(const std::pair<size_t, size_t> &pos, const grid_t &grid) const;
        void addPendingBodyPart(std::shared_ptr<IGameModule> gameModule);
        void ensurePreviousPositionsInitialized(std::shared_ptr<IGameModule> gameModule);
    };

#endif /* !NIBBLERHEADENTITY_HPP_ */
