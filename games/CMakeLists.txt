add_library(gameTemplate STATIC
    GameTemplate.hpp
    GameTemplate.cpp
)

target_compile_options(gameTemplate PRIVATE -fPIC)

add_subdirectory(entities)
add_subdirectory(snake)
add_subdirectory(menu)

add_dependencies(arcade_snake entities)

add_dependencies(arcade_menu entities)

add_dependencies(gameTemplate entities)

target_include_directories(gameTemplate PRIVATE . ../include)

target_link_libraries(arcade_snake entities gameTemplate)

target_link_libraries(arcade_menu entities gameTemplate)

