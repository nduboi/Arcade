add_executable(arcade
        main.cpp
        Program.cpp
        Program.hpp
)

add_subdirectory(LibLoader)
add_subdirectory(entities)
add_subdirectory(window)
add_subdirectory(games)

target_link_libraries(arcade LibLoader WindowModule GameModule EntitiesModules)

target_include_directories(arcade PRIVATE ../include window/include games/include entities/include)

add_custom_command(TARGET arcade POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade>/arcade"
        "$<TARGET_FILE_DIR:arcade>/../../arcade")
