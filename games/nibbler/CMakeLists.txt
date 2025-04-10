add_library(arcade_nibbler SHARED
        main.cpp
        NibblerGame.cpp
        ../GameTemplate.cpp
        ../entities/AEntity.cpp
        ../entities/VoidEntity.cpp
        ../entities/ScoreEntityHUD.cpp
        ../entities/HighScoreEntityHUD.cpp
        ../entities/TimeEntityHUD.cpp
        ../entities/TextEntityHUD.cpp
        ../entities/BigTextEntityHUD.cpp
        NibblerHeadEntity.cpp
        NibblerTailEntity.cpp
        FoodEntity.cpp
        MapManager.cpp
        WallEntity.cpp
)

add_custom_command(TARGET arcade_nibbler POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_nibbler>/libarcade_nibbler.so"
        "$<TARGET_FILE_DIR:arcade_nibbler>/../../../lib/arcade_nibbler.so")

add_custom_target(copy_arcade_nibbler ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_nibbler>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_nibbler>" "$<TARGET_FILE_DIR:arcade_nibbler>/../../../lib/arcade_nibbler.so"
        DEPENDS arcade_nibbler)
