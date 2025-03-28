add_library(arcade_ncurses SHARED
        main.cpp
        NcursesEncapsulation.cpp
        NcursesEncapsulation.hpp
        arcadeNcurses.cpp
        arcadeNcurses.hpp
        arcadeNcursesEvent.cpp
        arcadeNcursesEvent.hpp
)

target_link_libraries(arcade_ncurses ncurses)

target_compile_options(arcade_ncurses PRIVATE -g3 -ggdb -O0 -Wall -Wextra -Wpedantic)

add_custom_command(TARGET arcade_ncurses POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_ncurses>/libarcade_ncurses.so"
        "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib/arcade_ncurses.so")

add_custom_target(copy_arcade_ncurses ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_ncurses>" "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib/arcade_ncurses.so"
        DEPENDS arcade_ncurses)
