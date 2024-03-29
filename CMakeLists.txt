#
# \file       CMakeLists.txt
# \author     GrandChris
# \date       2021-12-30
# \brief      Base project file
#

cmake_minimum_required(VERSION 3.20)

# Create the project
project("FileToHeader" CXX)

# Export compile commands for VSCode C++ Intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -fdiagnostics-color
    -Wall 
)

# add library
add_executable(${PROJECT_NAME})

# include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/source"
)

# add source files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/source/file_to_header/*.cpp"
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})
