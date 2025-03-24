add_subdirectory(snake)
add_subdirectory(minesweeper)

target_include_directories(arcade_snake PRIVATE ./ entities)
target_include_directories(arcade_menu PRIVATE ./ entities)
target_include_directories(arcade_minesweeper PRIVATE ./ entities)

