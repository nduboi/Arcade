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
        window_data.loadGameModule("./lib/arcade_menu.so");
        while (window_data.display->isOpen()) {
            IEvent::event_t event = window_data.event->pollEvents({});
            if (event == IEvent::event_t::CLOSE)
                window_data.display->closeWindow();
            if (event == IEvent::event_t::LEFT)
                printf("EVENT LEFT\n");
            if (event == IEvent::event_t::RIGHT)
                printf("EVENT RIGHT\n");
            if (event == IEvent::event_t::UP)
                printf("EVENT UP\n");
            if (event == IEvent::event_t::DOWN)
                printf("EVENT DOWN\n");
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
