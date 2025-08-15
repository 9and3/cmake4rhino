cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(sticker-generator
    VERSION 1.0.0
    DESCRIPTION "CMake sticker generator to be printed in c++"
    LANGUAGES CXX
)

add_executable(cmake-sticker ${CMAKE_CURRENT_SOURCE_DIR}/cmake-sticker.cc)
set_target_properties(cmake-sticker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake"
    OUTPUT_NAME "cmake-sticker"
)