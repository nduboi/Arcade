/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SnakeBodyEntity
*/

#ifndef SNAKEBODYENTITY_HPP_
#define SNAKEBODYENTITY_HPP_

#include "AEntity.hpp"
#include <map>

class SnakeBodyEntity : public AEntity {
    private:
        int _index;
        std::pair<int, int> _direction;
        std::map<std::string, std::string> _assetsName;

    public:
        SnakeBodyEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position, int index);
        ~SnakeBodyEntity() = default;

        std::string getSpriteName() const override;
        int getIndex() const;
        void updateDirection(std::pair<size_t, size_t> current, std::pair<size_t, size_t> next, std::pair<size_t, size_t> prev);
};

#endif /* !SNAKEBODYENTITY_HPP_ */
