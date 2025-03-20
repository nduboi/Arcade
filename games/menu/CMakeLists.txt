add_library(arcade_menu SHARED
    main.cpp
        Menu.cpp
        Menu.hpp
)

target_include_directories(arcade_menu PRIVATE . ../../include ../../src/LibLoader ../)

add_custom_command(TARGET arcade_menu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_menu>/libarcade_menu.so"
        "$<TARGET_FILE_DIR:arcade_menu>/../../../lib/arcade_menu.so")