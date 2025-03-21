/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** main
*/

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <exception>
#include "Core.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib]" << std::endl;
        return 84;
    }

    std::string lib = av[1];
    Core window_data;

    if (lib == "-h" || lib == "--help") {
        std::cout << "Run the program with lib as argument:" << std::endl;
        std::cout << "  ./arcade [lib]" << std::endl;
        window_data.displayAllLib();
        return 0;
    }

    try {
        window_data.loadDisplayModule(lib);
        window_data.loadGameModule("./lib/arcade_snake.so");
        window_data.loop();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
