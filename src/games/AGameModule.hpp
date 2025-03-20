/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
#define AGAMEMODULE_HPP_

#include "../common/IGameModule.hpp"

class AGameModule : public IGameModule {
    protected:
        std::string _name;
        size_t _highScore;
        size_t _score;
        std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> _entities;
    
    public:
        AGameModule();
        ~AGameModule() = default;

        std::size_t getHighScore() const override;
        void setHighScore(std::size_t highScore) override;
        std::size_t getScore() const override;
        void setScore(std::size_t score) override;
        std::vector<std::vector<std::vector<std::shared_ptr<IEntity>>>> getEntities() const override;
};

#endif /* !AGAMEMODULE_HPP_ */
