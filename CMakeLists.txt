# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Author: 2025 Andrea Settimi, cmake4rhino
# Distributed under the MIT License.
# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# Notes:
# TODO: find a mechanism to adapt he name for the tempalte everywhere --> cockiecutter
# TODO: test ci


cmake_minimum_required(VERSION 3.15)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------------------------------------------------------------------
# >>>>>>>>>>>>>>>>>>>>>>> INSERT Rhino plugin information here >>>>>>>>>>>>>>>>>>>>>>>
# --------------------------------------------------------------------------------------------------------------------------
set(PLUGIN_VERSION_MAJOR 1)
set(PLUGIN_VERSION_MINOR 0)
set(PLUGIN_VERSION_PATCH 0)
set(PLUGIN_VERSION_BUILD 0)
set(PLUGIN_VERSION "${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH}.${PLUGIN_VERSION_BUILD}")

set(PLUGIN_COMPANY_NAME "Your Own Organization")
set(PLUGIN_INTERNAL_NAME "cmake4rhino")
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

set(ICON_PATH "${CMAKE_SOURCE_DIR}/res/cmake4rhino.ico")
set(PLUGIN_ORIGINAL_FILENAME "${PLUGIN_INTERNAL_NAME}.rhp")

# --------------------------------------------------------------------------------------------------------------------------
# Options
# --------------------------------------------------------------------------------------------------------------------------
message(STATUS "==== Project Options =====================================================================================")
message(STATUS "  -DMFC_ROOT=...                                : Path to the MFC root directory")
set(MFC_ROOT "" CACHE PATH "")
message(STATUS "  -DRHINO8SDK_ROOT=...                          : Path to the Rhino 8 SDK root directory")
set(RHINO8SDK_ROOT "" CACHE PATH "")
# message(STATUS "  -DCMAKE_BUILD_TYPE=...                        : Build type (Debug or Release)")
# set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
message(STATUS "  -DRUN_POSTBUILD_RHINO=ON                      : Run Rhino just after the compilation (default: OFF)")
set(RUN_POSTBUILD_RHINO OFF CACHE BOOL "")
message(STATUS "  -DRHINO_EXE_PATH=...                           : Path to the Rhino executable (Rhino.exe) path directory")
set(RHINO_EXE_PATH "" CACHE PATH "")
message(STATUS "==========================================================================================================")

# --------------------------------------------------------------------------------------------------------------------------
# Source files, win resources and headers
# --------------------------------------------------------------------------------------------------------------------------
project(cmake4rhino LANGUAGES VERSION ${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH} CXX)

# generate the .rc file for the plugin
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake4rhino.rc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake4rhino.rc
    @ONLY
)

# src/headers and .rhp (aka .dll)
add_library(cmake4rhino SHARED)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
file(GLOB WIN32_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/cmake4rhino.rc
${CMAKE_CURRENT_SOURCE_DIR}/res/cmake4rhino.rc
)
target_sources(cmake4rhino PRIVATE
${SOURCES}
${WIN32_RESOURCES}
)

target_include_directories(cmake4rhino PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_precompile_headers(cmake4rhino PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/stdafx.h)

set_target_properties(cmake4rhino PROPERTIES SUFFIX ".rhp")
set_target_properties(cmake4rhino PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# pre-processor data for the plugin
target_compile_definitions(cmake4rhino PRIVATE
    PLUGIN_VERSION="${PLUGIN_VERSION}"
    PLUGIN_COMPANY_NAME=L\"${PLUGIN_COMPANY_NAME}\"
    PLUGIN_FILEVERSION_STR=L\"${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, ${PLUGIN_VERSION_BUILD}\"
    PLUGIN_INTERNAL_NAME=L\"${PLUGIN_INTERNAL_NAME}\"
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

# --------------------------------------------------------------------------------------------------------------------------
# Additional dependencies and options
# --------------------------------------------------------------------------------------------------------------------------
# Insert here your additional libraries or options (e.g., Boost, OpenCV, etc.)

# --------------------------------------------------------------------------------------------------------------------------
# Basic dependencies and features
# --------------------------------------------------------------------------------------------------------------------------
# integration of Microsoft Foundation Classes (MFC) with CMake
find_package(MFC REQUIRED)
# It should be set to ``1`` for the static MFC library, and
# ``2`` for the shared MFC library.  This is used in Visual Studio
# project files.
add_definitions(-D_AFXDLL)
set(CMAKE_MFC_FLAG 2)

# Rhino 8 SDK
find_package(Rhino8SDK REQUIRED)
target_include_directories(cmake4rhino PRIVATE ${RHINO8SDK_INCLUDE_DIR})
target_link_libraries(cmake4rhino PRIVATE
    ${RHINO8SDK_LIB_DIR}/RhinoCore.lib
    ${RHINO8SDK_LIB_DIR}/RhinoLibrary.lib
    ${RHINO8SDK_LIB_DIR}/rdk.lib
    ${RHINO8SDK_LIB_DIR}/opennurbs.lib
)

# Define required preprocessor macros
target_compile_definitions(cmake4rhino PRIVATE
    WIN64
    _WINDOWS
    _USRDLL
    _UNICODE
    UNICODE
    RHINO_LIB_DIR=${RHINO8SDK_LIB_DIR}
)
target_compile_options(cmake4rhino PRIVATE /UWIN32)  # Add this to undefine WIN64

# Set the precompiled variables for Debug/Release mode for VS multigeneator
target_compile_definitions(cmake4rhino PRIVATE
    $<$<CONFIG:Debug>:_DEBUG;RHINO_DEBUG_PLUGIN>
)
target_compile_definitions(cmake4rhino PRIVATE
    $<$<CONFIG:Release>:NDEBUG>
)

# --------------------------------------------------------------------------------------------------------------------------
# Post-build steps
# --------------------------------------------------------------------------------------------------------------------------
# FIXME: this is not working, the plugin is not installed afterwards
if (RUN_POSTBUILD_RHINO)
    message(STATUS "Running Rhino after build...")
    find_package(RhinoExe REQUIRED)
    add_custom_target(run_rhino ALL
        # COMMAND ${RHINO_EXE} /nosplash /runscript="!_RunPlugin ${CMAKE_BINARY_DIR}/cmake4rhino.rhp"
        COMMAND ${RHINO_EXE} /nosplash /runscript="-_PluginManager _Install \"${CMAKE_BINARY_DIR}/cmake4rhino.rhp\" _Enable _OK"
        COMMENT "Running Rhino with the built plugin in ${CMAKE_BINARY_DIR}/cmake4rhino.rhp"
        VERBATIM
    )
    add_dependencies(run_rhino cmake4rhino)
endif()