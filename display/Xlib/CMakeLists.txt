add_library(arcade_xlib SHARED
        main.cpp
        XlibEncapsulation.cpp
        XlibEncapsulation.hpp
        arcadeXlib.cpp
        arcadeXlib.hpp
        arcadeXlibEvent.cpp
        arcadeXlibEvent.hpp
)

find_package(Freetype REQUIRED)
find_package(X11 REQUIRED)

target_link_libraries(arcade_xlib X11::X11  Freetype::Freetype Xft)

set_target_properties(arcade_xlib PROPERTIES LINK_FLAGS "-Wl,--export-dynamic")

target_compile_options(arcade_xlib PRIVATE -g3 -ggdb -O0 -Wall -Wextra -Wpedantic)

add_custom_command(TARGET arcade_xlib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_xlib>/libarcade_xlib.so"
        "$<TARGET_FILE_DIR:arcade_xlib>/../../../lib/arcade_xlib.so")

add_custom_target(copy_arcade_xlib ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_xlib>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_xlib>" "$<TARGET_FILE_DIR:arcade_xlib>/../../../lib/arcade_xlib.so"
        DEPENDS arcade_xlib)
