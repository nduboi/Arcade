add_subdirectory(snake)

target_include_directories(arcade_snake PRIVATE ./ entities)
target_include_directories(arcade_menu PRIVATE ./ entities)

