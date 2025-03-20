add_library(LibLoader STATIC
        LibLoader.cpp
        DynamicLib.cpp
)

target_include_directories(LibLoader PRIVATE ../../include)
