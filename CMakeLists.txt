cmake_minimum_required(VERSION 3.24)
project(images)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} main.cpp ${SRC})

add_custom_target(run ./${PROJECT_NAME})