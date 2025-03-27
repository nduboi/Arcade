add_library(arcade_sdl2 SHARED
    main.cpp
    arcadeSDL.cpp
    arcadeSDL.hpp
    arcadeSDLEvent.cpp
    arcadeSDLEvent.hpp
    SDLEncapsulation.cpp
    SDLEncapsulation.hpp
)

target_link_libraries(arcade_sdl2 SDL2 SDL2_image SDL2_ttf)

add_custom_command(TARGET arcade_sdl2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_sdl2>/libarcade_sdl2.so"
        "$<TARGET_FILE_DIR:arcade_sdl2>/../../../lib/arcade_sdl2.so")

add_custom_target(copy_arcade_sdl2 ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_sdl2>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_sdl2>" "$<TARGET_FILE_DIR:arcade_sdl2>/../../../lib/arcade_sdl2.so"
        DEPENDS arcade_sdl2)