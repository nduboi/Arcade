cmake_minimum_required(VERSION 3.25)
project(Arcade)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
add_compile_options("-fno-gnu-unique")

#add_subdirectory(libSDL2)
#add_subdirectory(libSFML)
add_subdirectory(libCACA)
add_subdirectory(games)
add_subdirectory(src)

target_link_libraries(arcade_caca LibLoader)

