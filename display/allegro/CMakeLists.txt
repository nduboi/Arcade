add_library(arcade_allegro5 SHARED
        main.cpp
        AllegroEncapsulation.cpp
        AllegroEncapsulation.hpp
        arcadeAllegro.cpp
        arcadeAllegro.hpp
        arcadeAllegroEvent.cpp
        arcadeAllegroEvent.hpp
)

target_link_libraries(arcade_allegro5 allegro allegro_ttf allegro_font allegro_image allegro_primitives)

set_target_properties(arcade_allegro5 PROPERTIES LINK_FLAGS "-Wl,--export-dynamic")

target_compile_options(arcade_allegro5 PRIVATE -g3 -ggdb -O0 -Wall -Wextra -Wpedantic)

add_custom_command(TARGET arcade_allegro5 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_allegro5>/libarcade_allegro5.so"
        "$<TARGET_FILE_DIR:arcade_allegro5>/../../../lib/arcade_allegro5.so")

add_custom_target(copy_arcade_allegro5 ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_allegro5>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_allegro5>" "$<TARGET_FILE_DIR:arcade_allegro5>/../../../lib/arcade_allegro5.so"
        DEPENDS arcade_allegro5)
