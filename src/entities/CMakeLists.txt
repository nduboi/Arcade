add_library(EntitiesModules STATIC
    AEntity.cpp
)

target_include_directories(EntitiesModules PRIVATE ../../include include)
