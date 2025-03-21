add_library(arcade_snake SHARED
    main.cpp
    SnakeGame.cpp
    ../GameTemplate.cpp
    ../entities/AEntity.cpp
    ../entities/VoidEntity.cpp
)

add_custom_command(TARGET arcade_snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_snake>/libarcade_snake.so"
        "$<TARGET_FILE_DIR:arcade_snake>/../../../lib/arcade_snake.so")