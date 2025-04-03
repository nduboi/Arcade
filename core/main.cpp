/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** main
*/

#include <dlfcn.h>
#include <iostream>
#include <string>
#include "Exception.hpp"
#include "Core.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: ./arcade [lib]" << std::endl;
        return 84;
    }

    std::string lib = av[1];

    try {
        Core window_data(lib);
        window_data.loop();
    } catch (HelpException &) {
        return 0;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
