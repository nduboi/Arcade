/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** PacmanGame
*/

#ifndef PACMANGAME_HPP_
#define PACMANGAME_HPP_

#include "GameTemplate.hpp"
#include "PacmanEntity.hpp"

class PacmanGame : public GameTemplate {
    public:
        PacmanGame();
        ~PacmanGame() = default;

        std::vector<std::shared_ptr<IEntity>> getHUD() const override;

        void update(std::shared_ptr<IGameModule> gameModule) override;

    protected:
    private:
        float _multiplier = 1.0f;
        int _round = 1;

        void setLayerBackground();
        void setLayerEntities();
        void setLayerInteract();

        void resetGame(std::shared_ptr<IGameModule> gameModule);
};

#endif /* !PACMANGAME_HPP_ */
