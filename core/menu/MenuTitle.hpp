/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-eliott.tesnier
** File description:
** MenuTitle
*/

#ifndef MENU_TITLE_HPP
#define MENU_TITLE_HPP

#include <string>
#include <memory>
#include "IWindow.hpp"

class MenuTitle {
    private:
        std::shared_ptr<IWindow> _window;
    public:
        // Constructor
        MenuTitle(const std::shared_ptr<IWindow> &window, const std::string& title = "Arcade Menu",
            const std::pair<int, int>& position = {100, 50}, int fontSize = 24);

        // Method
        void draw(const std::shared_ptr<IWindow> &window);

        // Getter
        std::string getTitle() const;

        // Setter
        void setTitle(const std::string& title);
        void setPosition(const std::pair<int, int>& position);
        void setFontSize(int fontSize);

    private:
        // Variable
        std::string _title;
        std::pair<int, int> _position;
        int _fontSize;

};

#endif // MENU_TITLE_HPP
