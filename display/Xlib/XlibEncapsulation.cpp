#include "XlibEncapsulation.hpp"
#include <stdexcept>
#include <iostream>
#include <X11/Xft/Xft.h>
#include <cstring>
#include <sys/time.h>
#include <unistd.h>

namespace DisplayLib {
    XlibEncapsulation::XlibEncapsulation() {
        // Open display
        this->_display = XOpenDisplay(nullptr);
        if (!this->_display) {
            throw std::runtime_error("Failed to open X display.");
        }
        
        // Get default screen
        this->_screen = DefaultScreen(_display);
        
        // Create window with background pixel to reduce flicker
        this->_window = XCreateSimpleWindow(
            this->_display,
            RootWindow(this->_display, this->_screen),
            0, 0,                                 // Position
            this->_windowWidth, this->_windowHeight,          // Size
            0,                                    // Border width
            BlackPixel(this->_display, this->_screen),        // Border color
            WhitePixel(this->_display, this->_screen)         // Background color
        );
        
        // Set window properties to reduce flickering
        XSetWindowAttributes attrs;
        attrs.backing_store = WhenMapped;
        attrs.save_under = True;
        attrs.bit_gravity = StaticGravity;
        XChangeWindowAttributes(this->_display, this->_window, CWBackingStore | CWSaveUnder | CWBitGravity, &attrs);
        
        // Set window title
        XStoreName(this->_display, this->_window, "Arcade - X11");
        
        // Enable needed events
        XSelectInput(this->_display, this->_window,
            ExposureMask | KeyPressMask | KeyReleaseMask | 
            ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
            StructureNotifyMask
        );
        
        // Create graphics context
        XGCValues gcValues;
        gcValues.graphics_exposures = False;  // Reduce unnecessary events
        this->_gc = XCreateGC(this->_display, this->_window, GCGraphicsExposures, &gcValues);
        
        // Create our own back buffer using a Pixmap
        this->_backBuffer = XCreatePixmap(this->_display, this->_window, this->_windowWidth, this->_windowHeight,
                                   DefaultDepth(this->_display, this->_screen));
        this->_backGC = XCreateGC(this->_display, this->_backBuffer, GCGraphicsExposures, &gcValues);
        
        // Map window
        XMapWindow(this->_display, this->_window);
        
        // Wait for window to be visible
        XEvent event;
        while (1) {
            XNextEvent(this->_display, &event);
            if (event.type == MapNotify)
                break;
        }
        
        // Store initial window attributes
        XGetWindowAttributes(this->_display, this->_window, &this->_windowAttrs);
        
        // Set window state and initial visibility
        this->_isWindowOpen = true;
        
        // Clear back buffer
        XSetForeground(this->_display, this->_backGC, WhitePixel(this->_display, this->_screen));
        XFillRectangle(this->_display, this->_backBuffer, this->_backGC, 0, 0, this->_windowWidth, this->_windowHeight);
        
        // Synchronize to reduce flicker during initialization
        XSync(this->_display, False);
    }

    XlibEncapsulation::~XlibEncapsulation() {
        if (this->_backGC) {
            XFreeGC(this->_display, this->_backGC);
            this->_backGC = 0;
        }
        
        if (this->_backBuffer) {
            XFreePixmap(this->_display, this->_backBuffer);
            this->_backBuffer = 0;
        }
        
        if (this->_gc) {
            XFreeGC(this->_display, _gc);
            this->_gc = 0;
        }
        
        if (this->_window) {
            XDestroyWindow(this->_display, this->_window);
            this->_window = 0;
        }
        
        if (this->_display) {
            XCloseDisplay(this->_display);
            this->_display = nullptr;
        }
        
        this->_isWindowOpen = false;
    }

    void XlibEncapsulation::display() {
        // Rate limit updates to reduce flicker (max ~60 FPS)
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        unsigned long currentTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        
        if (currentTime - _lastUpdateTime < 16) { // ~60 FPS
            // Small delay to avoid excessive CPU usage
            usleep(1000); // 1ms sleep
            return;
        }
        
        // Handle pending events to avoid lag
        XEvent event;
        while (XCheckWindowEvent(this->_display, this->_window, ExposureMask, &event)) {
            handleExpose();
        }
        
        // Copy back buffer to window (this is our "double buffering")
        XCopyArea(this->_display, this->_backBuffer, this->_window, this->_gc,
                  0, 0, this->_windowWidth, this->_windowHeight, 0, 0);
        
        // Flush output buffer
        XFlush(this->_display);
        
        this->_lastUpdateTime = currentTime;
    }

    void XlibEncapsulation::clear() {
        // Clear the back buffer
        XSetForeground(this->_display, this->_backGC, WhitePixel(this->_display, this->_screen));
        XFillRectangle(this->_display, this->_backBuffer, this->_backGC, 0, 0, this->_windowWidth, this->_windowHeight);
    }

    void XlibEncapsulation::resizeWindow(size_t width, size_t height) {
        if (this->_windowWidth == width && this->_windowHeight == height)
            return;  // No change, avoid unnecessary operations
            
        this->_windowWidth = width;
        this->_windowHeight = height;
        
        XResizeWindow(this->_display, this->_window, width, height);
        
        // Recreate back buffer with new size
        if (this->_backBuffer) {
            XFreePixmap(this->_display, this->_backBuffer);
        }
        this->_backBuffer = XCreatePixmap(this->_display, this->_window, width, height,
             DefaultDepth(this->_display, this->_screen));
        
        // Clear the new back buffer
        XSetForeground(this->_display, this->_backGC, WhitePixel(this->_display, this->_screen));
        XFillRectangle(this->_display, this->_backBuffer, this->_backGC, 0, 0, width, height);
        XSync(this->_display, False);
    }

    bool XlibEncapsulation::isOpen() const {
        return this->_display != nullptr && this->_isWindowOpen;
    }

    void XlibEncapsulation::drawRectangle(int x, int y, int width, int height, const Color &color) {
        // Convert RGB to X11 color
        unsigned long xcolor = (color.r << 16) | (color.g << 8) | color.b;
        XSetForeground(this->_display, this->_backGC, xcolor);
        
        // Draw filled rectangle on back buffer
        XFillRectangle(this->_display, this->_backBuffer, this->_backGC, x, y, width, height);
    }

    void XlibEncapsulation::drawText(const std::string &text, int x, int y, const Color &color) {
        if (text.empty())
            return;

        XftFont *font = XftFontOpenName(this->_display, this->_screen, "assets/ARACADECLASSIC.TTF");
        if (!font) {
            std::cerr << "Failed to load TrueType font: ARACADECLASSIC" << std::endl;
            return;
        }

        XftColor xftColor;
        XRenderColor renderColor = {
            static_cast<unsigned short>(color.r * 257), // Convert 8-bit to 16-bit
            static_cast<unsigned short>(color.g * 257),
            static_cast<unsigned short>(color.b * 257),
            65535 // Alpha (fully opaque)
        };
        if (!XftColorAllocValue(this->_display, DefaultVisual(this->_display, this->_screen), DefaultColormap(this->_display, this->_screen), &renderColor, &xftColor)) {
            std::cerr << "Failed to allocate Xft color" << std::endl;
            XftFontClose(this->_display, font);
            return;
        }
        XftDraw *draw = XftDrawCreate(this->_display, this->_backBuffer, DefaultVisual(this->_display, this->_screen), DefaultColormap(this->_display, this->_screen));
        if (!draw) {
            std::cerr << "Failed to create XftDraw" << std::endl;
            XftColorFree(this->_display, DefaultVisual(this->_display, this->_screen), DefaultColormap(this->_display, this->_screen), &xftColor);
            XftFontClose(this->_display, font);
            return;
        }
        XftDrawStringUtf8(draw, &xftColor, font, x, y, reinterpret_cast<const FcChar8 *>(text.c_str()), text.length());
        XftDrawDestroy(draw);
        XftColorFree(this->_display, DefaultVisual(this->_display, this->_screen), DefaultColormap(this->_display, this->_screen), &xftColor);
        XftFontClose(this->_display, font);
    }

    std::pair<int, int> XlibEncapsulation::getWindowSize() {
        // Only query window attributes when needed
        XGetWindowAttributes(this->_display, this->_window, &this->_windowAttrs);
        return {this->_windowAttrs.width, this->_windowAttrs.height};
    }
    
    void XlibEncapsulation::handleExpose() {
        // Just copy the back buffer to the window
        XCopyArea(this->_display, this->_backBuffer, this->_window, this->_gc,
                  0, 0, this->_windowWidth, this->_windowHeight, 0, 0);
    }
}
