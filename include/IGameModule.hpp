/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <utility>

class IEntity;

typedef std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> grid_t;

typedef enum gameState_e {
    PLAYING,
    WIN,
    LOSE
} gameState_t;

class IGameModule {
    public:
        virtual ~IGameModule() = default;

        virtual std::size_t getHighScore() const = 0;
        virtual void setHighScore(std::size_t highScore) = 0;

        virtual std::size_t getScore() const = 0;
        virtual void setScore(std::size_t score) = 0;

        virtual grid_t getEntities() const = 0;
        virtual void setEntities(grid_t entities) = 0;

        virtual std::pair<size_t, size_t> getGridSize() const = 0;

        virtual bool getIsStarted() const = 0;
        virtual void setIsStarted(bool isStarted) = 0;

        virtual gameState_t getGameState() const = 0;
        virtual void setGameState(gameState_t gameState) = 0;

        virtual std::vector<std::shared_ptr<IEntity>> getHUD() const = 0;

        virtual size_t getTime() const = 0;
        virtual void setTime(size_t time) = 0;

        virtual void update(std::shared_ptr<IGameModule> gameModule) = 0;
};

#endif /* !IGAMEMODULE_HPP_ */
