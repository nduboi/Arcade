#include <iostream>
#include "arcadeXlib.hpp"
#include "arcadeXlibEvent.hpp"
#include "LoaderType.hpp"

extern "C" {
    IWindow *createInstance(void) {
        return new arcadeXlib();
    }
    
    IEvent *createEvent(std::shared_ptr<IWindow> Window) {
        return new arcadeXlibEvent(Window);
    }
    
    Loader::ModuleType_t getType(void) {
        return Loader::ModuleType_t::DISPLAY_MODULE;
    }
    
    __attribute__((constructor)) void construct() {
        #ifdef _DEBUG
            std::cout << "Loaded dynamic lib: Lib Xlib" << std::endl;
        #endif
    }
    
    __attribute__((destructor)) void deconstruct() {
        #ifdef _DEBUG
            std::cout << "Unloaded dynamic lib: Lib Xlib" << std::endl;
        #endif
    }
}
