add_library(EventModule STATIC
        EventModule.cpp
)

target_include_directories(EventModule PRIVATE ../../include ../LibLoader ../)
