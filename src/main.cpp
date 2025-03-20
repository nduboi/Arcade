#include <dlfcn.h>
#include <iostream>
#include <string>
#include <exception>

#include "Program.hpp"

int main(int ac, char **av) {
    try {
        Program window_data;

        if (ac == 1) {
            std::cout << "Run the program with lib as argument:" << std::endl;
            std::cout << "  ./arcade [lib]" << std::endl;
            window_data.displayAllLib();
            return 0;
        }
        window_data.loadDisplayModule(av[1]);
        if (ac >= 2)
            window_data.loadDisplayModule(av[2]);
        if (ac >= 3)
            window_data.loadGameModule(av[3]);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
