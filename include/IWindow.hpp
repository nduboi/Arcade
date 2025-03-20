/*
** EPITECH PROJECT, 2025
** B-OOP-400-NAN-4-1-arcade-albane.merian
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

class IWindow {
    public:
        virtual ~IWindow() = default;
        virtual void initWindow() = 0;
        virtual void display() = 0;
        virtual void closeWindow() = 0;
        virtual bool isOpen() = 0;
        virtual void clear() = 0;
    protected:
    private:
};

// extern "C" IWindow* createInstance();

#endif /* !IWINDOW_HPP_ */
