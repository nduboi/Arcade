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

    protected:
    private:
        void setLayerBackground();
        void setLayerEntities();
        void setLayerWalls();
        void setLayerHub();
        void setLayerBorders();
        void setLayerModules();
        void setLayerPortal();
        void setLayerDot();
        void setLayerBigDot();
        void setLayerSquareModules();
};

#endif /* !PACMANGAME_HPP_ */
