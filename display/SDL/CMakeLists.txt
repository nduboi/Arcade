add_library(arcade_sdl2 SHARED
    main.cpp
    arcadeSDL.cpp
    arcadeSDL.hpp
    arcadeSDLEvent.cpp
    arcadeSDLEvent.hpp
)

target_link_libraries(arcade_sdl2 SDL2 SDL2_image)

add_custom_command(TARGET arcade_sdl2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_sdl2>/libarcade_sdl2.so"
        "$<TARGET_FILE_DIR:arcade_sdl2>/../../../lib/arcade_sdl2.so")