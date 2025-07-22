cmake_minimum_required(VERSION 3.16)
project(ToDoApp)

#use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include nlohman_json
include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

#include dir
include_directories(include)

#get version
file(READ "${CMAKE_SOURCE_DIR}/Version.txt" VERSION_STRING)
string(STRIP "${VERSION_STRING}" VERSION_STRING)

#Platform
if(NOT DEFINED PLATFORM_NAME)
    set(PLATFORM_NAME "unknown")
endif()

set(EXECUTABLE_NAME "ToDoApp-${VERSION_STRING}-${PLATFORM_NAME}")

#gather main
add_executable(${EXECUTABLE_NAME} 
    src/ToDoElement.cpp
    src/ToDoList.cpp
    main.cpp)

#compiler warnings
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic)

#install(optional)
install(TARGETS ${EXECUTABLE_NAME} Destination bin)
