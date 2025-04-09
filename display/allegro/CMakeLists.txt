add_library(arcade_allegro SHARED
        main.cpp
        AllegroEncapsulation.cpp
        AllegroEncapsulation.hpp
        arcadeAllegro.cpp
        arcadeAllegro.hpp
        arcadeAllegroEvent.cpp
        arcadeAllegroEvent.hpp
)

target_link_libraries(arcade_allegro allegro allegro_ttf allegro_font allegro_image allegro_primitives)

set_target_properties(arcade_allegro PROPERTIES LINK_FLAGS "-Wl,--export-dynamic")

target_compile_options(arcade_allegro PRIVATE -g3 -ggdb -O0 -Wall -Wextra -Wpedantic)

add_custom_command(TARGET arcade_allegro POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_allegro>/libarcade_allegro.so"
        "$<TARGET_FILE_DIR:arcade_allegro>/../../../lib/arcade_allegro.so")

add_custom_target(copy_arcade_allegro ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_allegro>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_allegro>" "$<TARGET_FILE_DIR:arcade_allegro>/../../../lib/arcade_allegro.so"
        DEPENDS arcade_allegro)
