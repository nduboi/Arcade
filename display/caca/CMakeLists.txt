add_library(arcade_caca SHARED
    main.cpp
    arcadeCaca.cpp
    arcadeCaca.hpp
    arcadeCacaEvent.cpp
    arcadeCacaEvent.hpp
)

target_include_directories(arcade_caca PRIVATE . ../../include ../../src/LibLoader)

add_custom_command(TARGET arcade_caca POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_caca>/libarcade_caca.so"
        "$<TARGET_FILE_DIR:arcade_caca>/../../../lib/arcade_caca.so")