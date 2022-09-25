cmake_minimum_required(VERSION 3.10)

project(lab_1)

add_subdirectory(libs)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp
    src/engine.cpp
    src/collider.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)