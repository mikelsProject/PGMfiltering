cmake_minimum_required(VERSION 3.24)
project(images)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD)

file(GLOB source ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} main.cpp ${source})

add_custom_target(run ./${PROJECT_NAME})