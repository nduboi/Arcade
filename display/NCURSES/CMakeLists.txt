add_library(arcade_ncurses SHARED
    main.cpp
    arcadeNCURSES.cpp
    arcadeNCURSES.hpp
    arcadeNCURSESEvent.cpp
    arcadeNCURSESEvent.hpp
)

find_package(Curses REQUIRED)

target_link_libraries(arcade_ncurses PRIVATE ${CURSES_LIBRARIES})

target_include_directories(arcade_ncurses PRIVATE ${CURSES_INCLUDE_DIR})


add_custom_command(TARGET arcade_ncurses POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_ncurses>/libarcade_ncurses.so"
        "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib/arcade_ncurses.so")

add_custom_target(copy_arcade_ncurses ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_ncurses>" "$<TARGET_FILE_DIR:arcade_ncurses>/../../../lib/arcade_ncurses.so"
        DEPENDS arcade_ncurses)