# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Author: 2025 Andrea Settimi, cmake4rhino
# Distributed under the MIT License.
# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

cmake_minimum_required(VERSION 3.15)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/Utils.cmake)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print the logo, generator in ~logo/CMakeLists.txt
message(STATUS  " ")
execute_process(
    COMMAND ${CMAKE_SOURCE_DIR}/cmake/cmake-sticker.exe
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# ----------------------------------------------------------------------------------------------------------------------------------------
# >>> INSERT your plugin information here >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# ----------------------------------------------------------------------------------------------------------------------------------------
set(PLUGIN_VERSION_MAJOR 1)
set(PLUGIN_VERSION_MINOR 0)
set(PLUGIN_VERSION_PATCH 0)
set(PLUGIN_VERSION_BUILD 0)
set(PLUGIN_VERSION "${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH}.${PLUGIN_VERSION_BUILD}")

set(PLUGIN_COMPANY_NAME "Your Own Organization")
set(PLUGIN_NAME "cmake4rhino")
set(PLUGIN_ADDRESS "123 Developer Street City State 12345-6789")
set(PLUGIN_COUNTRY "My Country")
set(PLUGIN_PHONE "123-456-7890")
set(PLUGIN_FAX "123-456-7891")
set(PLUGIN_EMAIL "support@mycompany.com")
set(PLUGIN_WEBSITE "https://www.mycompany.com")
set(PLUGIN_UPDATE_URL "https://www.mycompany.com/update")
set(PLUGIN_LEGAL_COPYRIGHT "Copyright © 2025 Your Name or Company")
set(PLUGIN_FILE_DESCRIPTION "Rhino C++ Plugin in CMake for Custom Development")
set(PLUGIN_ID "5AC5581C-0559-492F-9E46-21574EE7F52B")

set(ICON_PATH "${CMAKE_SOURCE_DIR}/res/${PLUGIN_NAME}.ico")
set(PLUGIN_ORIGINAL_FILENAME "${PLUGIN_NAME}.rhp")

# ----------------------------------------------------------------------------------------------------------------------------------------
# Options
# ----------------------------------------------------------------------------------------------------------------------------------------
message(STATUS "==== Project Options ===================================================================================================")
message(STATUS "  -DMFC_ROOT=...                                 : Path to the MFC root directory")
set(MFC_ROOT "" CACHE PATH "")
message(STATUS "  -DRHINOSDK_ROOT=...                           : Path to the Rhino 8 SDK root directory")
set(RHINOSDK_ROOT "" CACHE PATH "")
message(STATUS "  -DRUN_POSTBUILD_RHINO=ON                       : Run Rhino just after the compilation (default: OFF)")
set(RUN_POSTBUILD_RHINO OFF CACHE BOOL "")
message(STATUS "  -DRHINO_EXE_PATH=...                           : Path to the Rhino executable (Rhino.exe) path directory")
set(RHINO_EXE_PATH "" CACHE PATH "")
message(STATUS "  -DBUILD_TESTS=ON                               : Enable tests (default: ON)")
set(BUILD_TESTS ON CACHE BOOL "")
message(STATUS "========================================================================================================================")

# ----------------------------------------------------------------------------------------------------------------------------------------
# Basic information, config, and project settings
# ----------------------------------------------------------------------------------------------------------------------------------------
project(${PLUGIN_NAME} LANGUAGES VERSION ${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH} CXX)

# define the main libraries of the cmake
set(PLUGIN_CORE "${PLUGIN_NAME}_core")
set(PLUGIN_RHP "${PLUGIN_NAME}")
set(PLUGIN_TESTS "${PLUGIN_NAME}_tests")

# integration of Microsoft Foundation Classes (MFC) with CMake
find_package(MFC REQUIRED)
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 1)  # ``1`` for the static MFC library, ``2`` for the shared MFC library

# generate the .rc file for the plugin
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.rc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_NAME}.rc 
    @ONLY
)

# ----------------------------------------------------------------------------------------------------------------------------------------
# Core section
# ----------------------------------------------------------------------------------------------------------------------------------------
message(STATUS "=== Compiling Core static library ======================================================================================")
# This is the core section. Here you can put all the code you require, it will be the only part of your source 
# code that can be unit tested. Note that it's not a library, but only a ensemble of source files compiled
# differently based on the .rhp or test (there are differences in the compilation flags for Rhino 8 SDK).
file(GLOB_RECURSE PLUGIN_CORE_SRC "${CMAKE_SOURCE_DIR}/src/${PLUGIN_NAME}/*.cpp")
recursive_print(PLUGIN_CORE_SRC HEADER "Compiling core library's sources:")

# ----------------------------------------------------------------------------------------------------------------------------------------
# >>> INSERT your 3rd party libraries (e.g. Boost, OpenCV, etc.) here >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# ----------------------------------------------------------------------------------------------------------------------------------------
# Uncomment the following lines to add 3rd party libraries, better if compiled as static libraries for Windows.
# Doing so, you are sure that all the symbols are exported and available for linking in Windows.
# erase the dummy.cpp file in cmake/dummy.cpp and reaplace it with "", next, add your 3rd party libraries then.
add_library(3RD_PARTY_LIBS STATIC ${CMAKE_SOURCE_DIR}/cmake/dummy.cpp)
# # Link both static and shared libraries
# target_link_libraries(3RD_PARTY_LIBS PUBLIC
#     SomeStaticLib
#     SomeSharedDLL
# )
# # Add include directories, definitions, etc.
# target_include_directories(3RD_PARTY_LIBS PUBLIC
#     ${SOME_INCLUDE_DIR}
# )

# ----------------------------------------------------------------------------------------------------------------------------------------
# .rhp library/plugin
# ----------------------------------------------------------------------------------------------------------------------------------------
message(STATUS "=== .rhp dynamic Rhino plugin ==========================================================================================")
# This is the plugin .rhp, which is a dynamic library (.dll) for Rhino basically. It contains their own entry points (<PluginName>App.h and
# <PluginName>PlugIn.h)
add_library(${PLUGIN_RHP} SHARED)  # .dll (aka .rhp later)

target_compile_definitions(${PLUGIN_RHP} PRIVATE RHINO_PLUGIN_BUILD)


file(GLOB PLUGIN_RHP_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
recursive_print(PLUGIN_RHP_SRC HEADER "Compiling plugin sources for the .rhp:")
target_sources(${PLUGIN_RHP} PRIVATE
    ${PLUGIN_RHP_SRC}
    ${PLUGIN_CORE_SRC}
)
target_include_directories(${PLUGIN_RHP} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Rhino 8 SDK specific compilation flags for .rhp
find_package(Rhino8SDK REQUIRED)
target_link_libraries(${PLUGIN_RHP} PRIVATE 
    RHINO_CORE_INTERFACE
    3RD_PARTY_LIBS
)
target_precompile_headers(${PLUGIN_RHP} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/stdafx.h)
target_compile_definitions(${PLUGIN_RHP} PRIVATE $<$<CONFIG:Debug>:_DEBUG;RHINO_DEBUG_PLUGIN>)
set_target_properties(${PLUGIN_RHP} PROPERTIES SUFFIX ".rhp")
set_target_properties(${PLUGIN_RHP} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
file(GLOB WIN32_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${PLUGIN_NAME}.rc
    res/${PLUGIN_NAME}.rc
)
target_sources(${PLUGIN_RHP} PRIVATE
    ${WIN32_RESOURCES}
)
target_compile_definitions(${PLUGIN_RHP} PRIVATE
    PLUGIN_VERSION="${PLUGIN_VERSION}"
    PLUGIN_COMPANY_NAME=L\"${PLUGIN_COMPANY_NAME}\"
    PLUGIN_FILEVERSION_STR=L\"${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, ${PLUGIN_VERSION_BUILD}\"
    PLUGIN_NAME=L\"${PLUGIN_NAME}\"
    PLUGIN_LEGAL_COPYRIGHT=L\"${PLUGIN_LEGAL_COPYRIGHT}\"
    PLUGIN_ORIGINAL_FILENAME=L\"${PLUGIN_ORIGINAL_FILENAME}\"
    PLUGIN_FILE_DESCRIPTION=L\"${PLUGIN_DESCRIPTION}\"
    PLUGIN_ADDRESS=L\"${PLUGIN_ADDRESS}\"
    PLUGIN_COUNTRY=L\"${PLUGIN_COUNTRY}\"
    PLUGIN_PHONE=L\"${PLUGIN_PHONE}\"
    PLUGIN_FAX=L\"${PLUGIN_FAX}\"
    PLUGIN_EMAIL=L\"${PLUGIN_EMAIL}\"
    PLUGIN_WEBSITE=L\"${PLUGIN_WEBSITE}\"
    PLUGIN_UPDATE_URL=L\"${PLUGIN_UPDATE_URL}\"
    PLUGIN_ID=L\"${PLUGIN_ID}\"
)

# ----------------------------------------------------------------------------------------------------------------------------------------
# Tests
# ----------------------------------------------------------------------------------------------------------------------------------------
# We integrate two types of tests:
# 1. Unit tests: these are the ones that test your core library functionalities. Note that the commands are not unit-testable.
# 2. Integration tests: these are testing only the commands on Rhino on a running headless instance of Rhino (via Rhino.Inside).
# 3. .. free to add more tests as you like, e.g. performance tests, etc.
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------------------------------------------------------------------
# Post-build steps
# ----------------------------------------------------------------------------------------------------------------------------------------
if (RUN_POSTBUILD_RHINO)
    message(STATUS "Running Rhino after build...")
    find_package(RhinoExe REQUIRED)
    add_custom_target(run_rhino ALL
        COMMAND ${RHINO_EXE} /nosplash "${CMAKE_BINARY_DIR}/$<CONFIG>/${PLUGIN_NAME}.rhp"
        COMMENT "Running Rhino with the built plugin in ${CMAKE_BINARY_DIR}/$<CONFIG>/${PLUGIN_NAME}.rhp"
        VERBATIM
    )
    add_dependencies(run_rhino ${PLUGIN_NAME})
endif()
message(STATUS "========================================================================================================================")