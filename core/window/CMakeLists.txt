add_library(WindowModule STATIC
        WindowModule.cpp
)

target_include_directories(WindowModule PRIVATE ../../include ../LibLoader ../)
