add_library(arcade_minesweeper SHARED
    main.cpp
    Cell.cpp
    MinesweeperGame.cpp
    ../GameTemplate.cpp
    ../entities/AEntity.cpp
    ../entities/ScoreEntityHUD.cpp
    ../entities/HighScoreEntityHUD.cpp
    ../entities/TimerEntityHUD.cpp
    ../entities/TextEntityHUD.cpp
    ../entities/BigTextEntityHUD.cpp
)

add_custom_command(TARGET arcade_minesweeper POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE_DIR:arcade_minesweeper>/libarcade_minesweeper.so"
        "$<TARGET_FILE_DIR:arcade_minesweeper>/../../../lib/arcade_minesweeper.so")

add_custom_target(copy_arcade_minesweeper ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_minesweeper>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_minesweeper>" "$<TARGET_FILE_DIR:arcade_minesweeper>/../../../lib/arcade_minesweeper.so"
        DEPENDS arcade_minesweeper)
