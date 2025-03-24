add_library(arcade_snake SHARED
    main.cpp
    SnakeGame.cpp
    ../GameTemplate.cpp
    ../entities/AEntity.cpp
    ../entities/VoidEntity.cpp
)

add_custom_command(TARGET arcade_snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_snake>/libarcade_snake.so"
        "$<TARGET_FILE_DIR:arcade_snake>/../../../lib/arcade_snake.so")

add_custom_target(copy_arcade_snake ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_snake>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_snake>" "$<TARGET_FILE_DIR:arcade_snake>/../../../lib/arcade_snake.so"
        DEPENDS arcade_snake)
