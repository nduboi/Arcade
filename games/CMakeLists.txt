add_library(gameTemplate STATIC
    GameTemplate.hpp
    GameTemplate.cpp
)

add_subdirectory(entities)
add_subdirectory(snake)

add_dependencies(arcade_snake entities)

add_dependencies(gameTemplate entities)

target_include_directories(gameTemplate PRIVATE . ../include)

target_link_libraries(arcade_snake entities gameTemplate)

