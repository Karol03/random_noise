cmake_minimum_required(VERSION 3.16)

project(random_noise VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -pedantic -O3 -static")

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apprandom_noise
    main.cpp

    randomnoiseelement.h
    randomnoise.h randomnoise.cpp
    categoriesdownloader.h categoriesdownloader.cpp
    trackdownloader.h trackdownloader.cpp
    trackselector.h trackselector.cpp
)

qt_add_qml_module(apprandom_noise
    URI random_noise
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(apprandom_noise PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apprandom_noise PRIVATE Qt6::Quick)

install(TARGETS apprandom_noise
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
