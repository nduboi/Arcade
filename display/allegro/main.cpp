#include <iostream>
#include "arcadeAllegro.hpp"
#include "arcadeAllegroEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
    IWindow *createInstance(void) {
        return new arcadeAllegro();
    }
    IEvent *createEvent(std::shared_ptr<IWindow> Window) {
        return new arcadeAllegroEvent(Window);
    }
    Loader::ModuleType_t getType(void) {
        return Loader::ModuleType_t::DISPLAY_MODULE;
    }
    __attribute__((constructor)) void construct() {
        #ifdef _DEBUG
            std::cout << "Loaded dynamic lib: Lib Allegro" << std::endl;
        #endif
    }
    __attribute__((destructor)) void deconstruct() {
        #ifdef _DEBUG
            std::cout << "Unloaded dynamic lib: Lib Allegro" << std::endl;
        #endif
    }
}
