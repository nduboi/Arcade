/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_
#include <vector>
#include <memory>
#include "IWindow.hpp"

enum action_e {
    USERNAME,
    GRAPHICLIB,
    GAMELIB,
    NOTHING,
};

struct Boxes {
    std::pair<int, int> posTop;
    std::pair<int, int> posBottom;
    action_e typesBoxes;
    bool selected;
    std::string _nameBoxes;
};

class IMenu {
    public:
        virtual ~IMenu() {}; // Declare the destructor
        virtual void displayMenu(const std::shared_ptr<IWindow> &window, std::vector<Boxes> _boxes,
            std::vector<std::string> libs, std::vector<std::string> games) = 0;
        virtual std::vector<Boxes> getBoxPoses() = 0;
        virtual std::string getUsername() = 0;
        virtual void setUsername(std::string username) = 0;

};

#endif /* !MENU_HPP_ */
