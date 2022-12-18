cmake_minimum_required(VERSION 3.13.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(PafosGame VERSION 1.0)

add_executable(${PROJECT_NAME} WIN32 main.cpp)

add_subdirectory(Core)
add_subdirectory(imgui)

find_library(direct11 d3d11.lib PATHS "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64")

if(${direct11} STREQUAL direct11-NOTFOUND)
    message(FATAL_ERROR "not found d3d11.lib")
else()
    message(STATUS "d3d11 found as ${direct11}")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC imgui)
target_include_directories(${PROJECT_NAME} PUBLIC Core)


target_link_directories(${PROJECT_NAME} PRIVATE Core)
target_link_directories(${PROJECT_NAME} PRIVATE imgui)

target_link_libraries(${PROJECT_NAME} Core)
target_link_libraries(${PROJECT_NAME} ${direct11})
target_link_libraries(${PROJECT_NAME} imgui)