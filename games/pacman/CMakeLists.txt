add_library(arcade_pacman SHARED
    main.cpp
    PacmanGame.cpp
    ../GameTemplate.cpp
    ../entities/AEntity.cpp
    ../entities/VoidEntity.cpp
    ../entities/ScoreEntityHUD.cpp
    ../entities/HighScoreEntityHUD.cpp
    ../entities/TimeEntityHUD.cpp
    ../entities/BigTextEntityHUD.cpp
    WallEntity.cpp
    PacmanEntity.cpp
    DotEntity.cpp
    BigDotEntity.cpp
    GhostEntity.cpp
    RedGhost.cpp
)

add_custom_command(TARGET arcade_pacman POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_pacman>/libarcade_pacman.so"
        "$<TARGET_FILE_DIR:arcade_pacman>/../../../lib/arcade_pacman.so")

add_custom_target(copy_arcade_pacman ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_pacman>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_pacman>" "$<TARGET_FILE_DIR:arcade_pacman>/../../../lib/arcade_pacman.so"
        DEPENDS arcade_pacman)
