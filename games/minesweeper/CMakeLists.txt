add_library(arcade_minesweeper SHARED
    main.cpp
    Cell.cpp
    MinesweeperGame.cpp
    ../GameTemplate.cpp
    ../entities/AEntity.cpp
    ../entities/VoidEntity.cpp
)

add_custom_command(TARGET arcade_minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_minesweeper>/libarcade_minesweeper.so"
        "$<TARGET_FILE_DIR:arcade_minesweeper>/../../../lib/arcade_minesweeper.so")
