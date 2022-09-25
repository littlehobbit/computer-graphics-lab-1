cmake_minimum_required(VERSION 3.10)

project(lab_1)

add_subdirectory(libs)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    src/engine.cpp
    src/collider.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)