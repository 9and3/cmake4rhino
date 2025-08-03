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
# >>> INSERT your plugin information here >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

set(PLUGIN_CORE "${PLUGIN_NAME}_core")
set(PLUGIN_RHP "${PLUGIN_NAME}")
set(CMAKE_PLUGIN_TESTS "${PLUGIN_NAME}_tests")

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

# We divide the source files into two categories, corresponding to 2 target libraries this CMake is generating:
# 1. rhino plugin .rhp: Sources that include the plugin headers (<yourpluginname>App.h and <yourpluginname>PlugIn.h) (for the core library)
#    This is because they are the entry points for the plugin .rhp, thy causing problems if incldued in the static core library.
# 2. core .lib: Sources that do not include the plugin headers (for the core library .lib). In order to unit test, we need to compile your 
#    added files outside the .rhp structure as a static library (because .ddll in Windows do not export all symbols by default as
#    in UNIX systems).
file(GLOB_RECURSE ALL_CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
find_sources_with_includes(
    SOURCES ${ALL_CPP_SOURCES}
    INCLUDES ${PLUGIN_NAME}App.h ${PLUGIN_NAME}PlugIn.h
    out_with SRC_WITH_INCLUDES
    out_without SRC_WITHOUT_INCLUDES
)
print_list_on_newlines(SRC_WITHOUT_INCLUDES HEADER "Sources without includes (for core only):")
print_list_on_newlines(SRC_WITH_INCLUDES HEADER "Sources with includes (for .rhp plugin library):")

# ----------------------------------------------------------------------------------------------------------------------------------------
# Core library
# ----------------------------------------------------------------------------------------------------------------------------------------
message(STATUS "=== Compiling Core static library ======================================================================================")
# This is the core library. Since, static it can be linked to the plugin .rhp or any other library or executable (e.g. tests).
add_library(${PLUGIN_CORE} STATIC)  # .lib for multiple linkage (.rhp, tests)

# Add all the files besides the entry points for the .rhl plugin (<PluginName>App.h and <PluginName>PlugIn.h and all the files that
# includ them as the commandds)
target_sources(${PLUGIN_CORE} PUBLIC ${SRC_WITHOUT_INCLUDES})

# Rhino 8 SDK
find_package(Rhino8SDK REQUIRED)
target_link_libraries(${PLUGIN_CORE} PUBLIC RHINO_CORE_INTERFACE)

target_include_directories(${PLUGIN_CORE} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}/include/${PLUGIN_NAME}
)
target_precompile_headers(${PLUGIN_CORE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/stdafx.h)

# >>> Insert here all the additional dependencies and options for the core library >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# ... e.g., Boost, OpenCV, etc.


# ----------------------------------------------------------------------------------------------------------------------------------------
# TODO: test
# ----------------------------------------------------------------------------------------------------------------------------------------

add_executable(exec_test_rh
    ${CMAKE_CURRENT_SOURCE_DIR}/temp/exec_test/main.cpp
)
target_link_libraries(exec_test_rh PRIVATE
    ${PLUGIN_CORE}
    # RHINO_CORE_INTERFACE
)
set_target_properties(exec_test_rh PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)

# # ----------------------------------------------------------------------------------------------------------------------------------------
# # .rhp library/plugin
# # ----------------------------------------------------------------------------------------------------------------------------------------
# message(STATUS "=== .rhp dynamic Rhino plugin ==========================================================================================")
# # This is the plugin .rhp, which is a dynamic library (.dll) for Rhino basically. It contains their own entry points.
# # Change the .dll to .rhp so Rhino can load it
# add_library(${PLUGIN_RHP} SHARED)  # .dll (aka .rhp later)

# # Add the <PluginName>App.h and <PluginName>PlugIn.h and all the commands
# target_sources(${PLUGIN_RHP} PRIVATE ${SRC_WITH_INCLUDES})

# message(STATUS "Found ${CMD_SOURCES} as command sources")

# target_link_libraries(${PLUGIN_RHP} PRIVATE ${PLUGIN_CORE})
# set_target_properties(${PLUGIN_RHP} PROPERTIES SUFFIX ".rhp")
# set_target_properties(${PLUGIN_RHP} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
# )
# file(GLOB WIN32_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#     ${PLUGIN_NAME}.rc
#     res/${PLUGIN_NAME}.rc
# )
# target_sources(${PLUGIN_RHP} PRIVATE
#     ${WIN32_RESOURCES}
# )
# # pre-processor data for the plugin
# target_compile_definitions(${PLUGIN_RHP} PRIVATE
#     PLUGIN_VERSION="${PLUGIN_VERSION}"
#     PLUGIN_COMPANY_NAME=L\"${PLUGIN_COMPANY_NAME}\"
#     PLUGIN_FILEVERSION_STR=L\"${PLUGIN_VERSION_MAJOR}, ${PLUGIN_VERSION_MINOR}, ${PLUGIN_VERSION_PATCH}, ${PLUGIN_VERSION_BUILD}\"
#     PLUGIN_NAME=L\"${PLUGIN_NAME}\"
#     PLUGIN_LEGAL_COPYRIGHT=L\"${PLUGIN_LEGAL_COPYRIGHT}\"
#     PLUGIN_ORIGINAL_FILENAME=L\"${PLUGIN_ORIGINAL_FILENAME}\"
#     PLUGIN_FILE_DESCRIPTION=L\"${PLUGIN_DESCRIPTION}\"
#     PLUGIN_ADDRESS=L\"${PLUGIN_ADDRESS}\"
#     PLUGIN_COUNTRY=L\"${PLUGIN_COUNTRY}\"
#     PLUGIN_PHONE=L\"${PLUGIN_PHONE}\"
#     PLUGIN_FAX=L\"${PLUGIN_FAX}\"
#     PLUGIN_EMAIL=L\"${PLUGIN_EMAIL}\"
#     PLUGIN_WEBSITE=L\"${PLUGIN_WEBSITE}\"
#     PLUGIN_UPDATE_URL=L\"${PLUGIN_UPDATE_URL}\"
#     PLUGIN_ID=L\"${PLUGIN_ID}\"
# )

# # ----------------------------------------------------------------------------------------------------------------------------------------
# # Tests
# # ----------------------------------------------------------------------------------------------------------------------------------------
# if (BUILD_TESTS)
#     add_subdirectory(tests)
# endif()

# # ----------------------------------------------------------------------------------------------------------------------------------------
# # Post-build steps
# # ----------------------------------------------------------------------------------------------------------------------------------------
# if (RUN_POSTBUILD_RHINO)
#     message(STATUS "Running Rhino after build...")
#     find_package(RhinoExe REQUIRED)
#     add_custom_target(run_rhino ALL
#         COMMAND ${RHINO_EXE} /nosplash "${CMAKE_BINARY_DIR}/$<CONFIG>/${PLUGIN_NAME}.rhp"
#         COMMENT "Running Rhino with the built plugin in ${CMAKE_BINARY_DIR}/$<CONFIG>/${PLUGIN_NAME}.rhp"
#         VERBATIM
#     )
#     add_dependencies(run_rhino ${PLUGIN_NAME})
# endif()
# message(STATUS "========================================================================================================================")