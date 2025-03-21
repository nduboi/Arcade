add_library(entities STATIC
    AEntity.cpp
    VoidEntity.cpp
)

target_compile_options(entities PRIVATE -fPIC)
