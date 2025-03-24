add_library(arcade_caca SHARED
    main.cpp
    arcadeCaca.cpp
    arcadeCaca.hpp
    arcadeCacaEvent.cpp
    arcadeCacaEvent.hpp
)

add_custom_command(TARGET arcade_caca POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_caca>/libarcade_caca.so"
        "$<TARGET_FILE_DIR:arcade_caca>/../../../lib/arcade_caca.so")

add_custom_target(copy_arcade_caca ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_caca>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_caca>" "$<TARGET_FILE_DIR:arcade_caca>/../../../lib/arcade_caca.so"
        DEPENDS arcade_caca)