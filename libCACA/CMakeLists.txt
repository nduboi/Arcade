add_library(arcade_caca SHARED
    main.cpp
    arcade_caca.cpp
    arcade_caca.hpp
)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

target_include_directories(arcade_caca PRIVATE . ../include ../src/LibLoader)

add_custom_command(TARGET arcade_caca POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_caca>/libarcade_caca.so"
        "$<TARGET_FILE_DIR:arcade_caca>/../../lib/arcade_caca.so")