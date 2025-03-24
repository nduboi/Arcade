add_library(arcade_menu SHARED
    main.cpp
    Menu.cpp
    ../games/entities/AEntity.cpp
    ../games/entities/VoidEntity.cpp
)

add_custom_command(TARGET arcade_menu POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_menu>/libarcade_menu.so"
        "$<TARGET_FILE_DIR:arcade_menu>/../../lib/arcade_menu.so")

add_custom_target(copy_arcade_menu ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_menu>/../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_menu>" "$<TARGET_FILE_DIR:arcade_menu>/../../lib/arcade_menu.so"
        DEPENDS arcade_menu)
