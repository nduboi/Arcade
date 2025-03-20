add_library(arcade_sfml SHARED
    main.cpp
    arcadeSFML.cpp
    arcadeSFML.hpp
    arcadeSFMLEvent.cpp
    arcadeSFMLEvent.hpp
)

target_include_directories(arcade_sfml PRIVATE . ../../include ../../src/LibLoader)

target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET arcade_sfml POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_sfml>/libarcade_sfml.so"
        "$<TARGET_FILE_DIR:arcade_sfml>/../../../lib/arcade_sfml.so")