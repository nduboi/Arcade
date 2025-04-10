/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** GhostEntity
*/

#ifndef GHOSTENTITY_HPP_
#define GHOSTENTITY_HPP_

#include <chrono>

#include "AEntity.hpp"

class GhostEntity : public AEntity {
    public:
        enum GhostState {
            CHASED,
            CHASING,
            WAITING,
            TRAVELING,
        };

    protected:
        float _multiplier = 1.0f;
        std::chrono::time_point<std::chrono::steady_clock> _animationTime;
        std::array<std::string, 2> _spriteNames;
        std::array<std::string, 4> _spriteChasedNames;
        std::string _spriteEyeName;
        std::pair<size_t, size_t> _spawnPosition;
        std::pair<size_t, size_t> _begPoint;
        GhostState _state;
        std::size_t _waitingTime = 0;
        std::chrono::time_point<std::chrono::steady_clock> _waitingPoint;

        std::shared_ptr<IEntity> _pacman;

        float _speedTime;
        std::chrono::time_point<std::chrono::steady_clock> _lastMove;

        bool moveToClosestFreeCell(std::shared_ptr<IGameModule> gameModule, std::pair<size_t, size_t> newPos);

        std::chrono::time_point<std::chrono::steady_clock> _chasedTime;
        bool _wasGettingChased = false;

    public:
        ~GhostEntity() = default;

        std::string getSpriteName() const override;

        void setState(GhostState state);
        GhostState getState() const;

        void setSpawnPosition(std::pair<size_t, size_t> spawnPosition);
        std::pair<size_t, size_t> getSpawnPosition() const;

        void setSpeedTime(float speedTime);
        float getSpeedTime() const;

        void setMultiplier(float multiplier);
        float getMultiplier() const;

        void setWaitingTime(std::size_t waitingTime);
        std::size_t getWaitingTime() const;

        void updateWaitingTime(std::shared_ptr<IGameModule> gameModule);

        void onInteract(std::shared_ptr<IGameModule> gameModule);

        void setWasGettingChased(bool wasGettingChased);
        bool getWasGettingChased() const;

        std::shared_ptr<IEntity> getPacman();
};

#endif /* !GHOSTENTITY_HPP_ */
