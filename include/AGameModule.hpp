/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include "IGameModule.hpp"

class AGameModule : public IGameModule {
    protected:
        std::string _name;
        size_t _highScore;
        size_t _score;
        grid_t entities;
    
    public:
        AGameModule();
        ~AGameModule() = default;

        std::size_t getHighScore() const override;
        void setHighScore(std::size_t highScore) override;
        std::size_t getScore() const override;
        void setScore(std::size_t score) override;
        grid_t getEntities() const override;
};

#endif /* !AGAMEMODULE_HPP_ */
