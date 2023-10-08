cmake_minimum_required(VERSION 3.26)
project(dt047gproject_conway)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH /usr/share/SFML)

find_package(PkgConfig)
find_package(docopt COMPONENTS CXX REQUIRED)
find_package(SFML REQUIRED system window graphics audio)

include_directories(${DOCOPT_INCLUDE_DIRS})

add_executable(dt047gproject_conway main.cpp
        Settings.cpp
        Settings.h
        Property.cpp
        Property.h
        BaseWindow.cpp
        BaseWindow.h
        ConwayGrid.cpp
        ConwayGrid.h
        Window.cpp)
target_link_libraries(dt047gproject_conway docopt sfml-graphics sfml-audio)
