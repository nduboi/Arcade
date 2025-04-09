# Find Qt5 packages
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Set Qt5 specific properties
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(arcade_qt5 SHARED
    main.cpp
    arcadeQT.cpp
    arcadeQT.hpp
    arcadeQTEvent.cpp
    arcadeQTEvent.hpp
)

# Link with Qt5 libraries instead of SFML
target_link_libraries(arcade_qt5 Qt5::Core Qt5::Widgets)

set_target_properties(arcade_qt5 PROPERTIES LINK_FLAGS "-Wl,--export-dynamic")

add_custom_command(TARGET arcade_qt5 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:arcade_qt5>/libarcade_qt5.so"
        "$<TARGET_FILE_DIR:arcade_qt5>/../../../lib/arcade_qt5.so")

add_custom_target(copy_arcade_qt5 ALL
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:arcade_qt5>/../../../lib"
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:arcade_qt5>" "$<TARGET_FILE_DIR:arcade_qt5>/../../../lib/arcade_qt5.so"
        DEPENDS arcade_qt5)
