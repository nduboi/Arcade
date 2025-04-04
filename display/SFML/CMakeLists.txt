add_library(arcade_sfml SHARED
    main.cpp
    arcadeSFML.cpp
    arcadeSFML.hpp
    arcadeSFMLEvent.cpp
    arcadeSFMLEvent.hpp
)

target_link_libraries(arcade_sfml sfml-graphics sfml-window sfml-system)

set_target_properties(arcade_sfml PROPERTIES LINK_FLAGS "-Wl,--export-dynamic")

add_custom_command(TARGET arcade_sfml POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_sfml>/libarcade_sfml.so"
        "$<TARGET_FILE_DIR:arcade_sfml>/../../../lib/arcade_sfml.so")

add_custom_target(copy_arcade_sfml ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_sfml>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_sfml>" "$<TARGET_FILE_DIR:arcade_sfml>/../../../lib/arcade_sfml.so"
        DEPENDS arcade_sfml)
