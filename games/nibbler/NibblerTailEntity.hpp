/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** NibblerTailEntity
*/

#ifndef NIBBLERTAILENTITY_HPP_
#define NIBBLERTAILENTITY_HPP_

#include "AEntity.hpp"
#include <map>

class NibblerTailEntity : public AEntity {
    private:
        int _index;
        std::pair<int, int> _direction;
        std::map<std::string, std::string> _assetsName;

    public:
        NibblerTailEntity(std::size_t color, std::string text, std::pair<size_t, size_t> position, int index);
        ~NibblerTailEntity() = default;

        std::string getSpriteName() const override;
        int getIndex() const;
        void updateDirection(std::pair<size_t, size_t> current, std::pair<size_t, size_t> next, std::pair<size_t, size_t> prev);
};

#endif /* !NIBBLERTAILENTITY_HPP_ */
