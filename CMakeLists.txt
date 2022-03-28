cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(asteroids VERSION 0.8)

find_package(glfw3 CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(asteroids main.cpp ${SRC_FILES} src/glad.c)

target_link_libraries(asteroids glfw)

target_include_directories(asteroids PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)