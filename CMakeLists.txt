cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PafosGame VERSION 1.0)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

add_subdirectory(Core)

target_include_directories(${PROJECT_NAME} PUBLIC Core)

target_link_directories(${PROJECT_NAME} PRIVATE Core)

target_link_libraries(${PROJECT_NAME} Core)