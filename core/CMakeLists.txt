add_executable(arcade
        main.cpp
        Core.cpp
        Core.hpp
        Saver.cpp
        Saver.hpp
)

add_custom_command(TARGET arcade POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade>/arcade"
        "$<TARGET_FILE_DIR:arcade>/../../arcade")

add_custom_target(copy_arcade ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade>/../.."
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade>" "$<TARGET_FILE_DIR:arcade>/../../arcade"
        DEPENDS arcade)

add_dependencies(arcade LibLoader WindowModule GameModule EventModule MenuModule)

add_subdirectory(LibLoader)
add_subdirectory(window)
add_subdirectory(games)
add_subdirectory(menu)
add_subdirectory(event)

target_link_libraries(arcade LibLoader WindowModule GameModule EventModule MenuModule)
target_include_directories(arcade PRIVATE window games entities event menu LibLoader ./)
target_include_directories(EventModule PRIVATE LibLoader ./)
target_include_directories(GameModule PRIVATE ./)
target_include_directories(MenuModule PRIVATE ./)
target_include_directories(WindowModule PRIVATE ./ LibLoader)
target_include_directories(LibLoader PRIVATE ./)
target_include_directories(arcade_snake PRIVATE LibLoader ./)
target_include_directories(arcade_pacman PRIVATE LibLoader ./)
target_include_directories(arcade_minesweeper PRIVATE LibLoader ./)
target_include_directories(arcade_sfml PRIVATE LibLoader ./)
target_include_directories(arcade_sdl2 PRIVATE LibLoader ./)
target_include_directories(arcade_ncurses PRIVATE LibLoader ./)
target_include_directories(arcade_allegro PRIVATE LibLoader ./)
