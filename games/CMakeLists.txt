add_subdirectory(snake)
add_subdirectory(minesweeper)
add_subdirectory(pacman)
add_subdirectory(nibbler)

target_include_directories(arcade_snake PRIVATE ./ entities)
target_include_directories(arcade_minesweeper PRIVATE ./ entities)
target_include_directories(arcade_pacman PRIVATE ./ entities)
target_include_directories(arcade_nibbler PRIVATE ./ entities)
