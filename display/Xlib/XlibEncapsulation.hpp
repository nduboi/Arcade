#ifndef XLIBENCAPSULATION_HPP
#define XLIBENCAPSULATION_HPP

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xlocale.h>
#include <X11/Xresource.h>
#include <X11/Xcursor/Xcursor.h>
#include <X11/X.h>
// Remove the Xdbe include to avoid dependency
#include <string>
#include <utility>
#include <cstdint>

namespace DisplayLib {
    struct Color {
        uint8_t r, g, b, a = 255;
    };

    class XlibEncapsulation {
    private:
        Display *_display = nullptr;
        Window _window;
        GC _gc;
        int _screen;
        bool _isWindowOpen = false;
        
        // Track window size to reduce unnecessary repaints
        int _windowWidth = 1620;
        int _windowHeight = 900;
        
        // Last time the display was updated
        unsigned long _lastUpdateTime = 0;
        
        // Cache for window properties
        XWindowAttributes _windowAttrs;
        
        // For double-buffering (using pixmaps instead of Xdbe)
        Pixmap _backBuffer = 0;
        GC _backGC = 0;

    public:
        XlibEncapsulation();
        ~XlibEncapsulation();

        void display();
        void clear();
        void resizeWindow(size_t width, size_t height);
        bool isOpen() const;
        void drawRectangle(int x, int y, int width, int height, const Color &color);
        void drawText(const std::string &text, int x, int y, const Color &color);
        std::pair<int, int> getWindowSize();
        
        // Additional accessors for event handling
        Display* getDisplay() const { return _display; }
        Window getWindow() const { return _window; }
        
        // Handle expose events more efficiently
        void handleExpose();
    };
}

#endif // XLIBENCAPSULATION_HPP
