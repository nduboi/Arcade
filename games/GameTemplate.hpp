/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** GameTemplate
*/

#ifndef GameTemplate_HPP_
#define GameTemplate_HPP_

#include "IGameModule.hpp"
#include <chrono>

class GameTemplate : public IGameModule {
    protected:
        std::size_t _highScore;
        std::size_t _score;
        grid_t _entities;
        bool _isStarted;
        gameState_t _gameState;
        std::chrono::time_point<std::chrono::steady_clock> _time;

    public:
        GameTemplate() = default;
        ~GameTemplate() = default;

        std::size_t getHighScore() const override;
        void setHighScore(std::size_t highScore) override;
        std::size_t getScore() const override;
        void setScore(std::size_t score) override;
        grid_t getEntities() const override;
        void setEntities(grid_t entities) override;
        std::pair<size_t, size_t> getGridSize() const override;
        bool getIsStarted() const override;
        void setIsStarted(bool isStarted) override;
        gameState_t getGameState() const override;
        void setGameState(gameState_t gameState) override;
        std::vector<std::shared_ptr<IEntity>> getHUD() const override;
        size_t getTime() const override;
        void setTime(size_t time) override;
};

#endif /* !AGAMEMODULE_HPP_ */
