# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# Author: 2025 Andrea Settimi, cmake4rhino
# Distributed under the MIT License.
# //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

# TODOD: try to integrate the cmake presets .CMakePresets.json

cmake_minimum_required(VERSION 3.15)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FIXME: find a good logic with CI integration for logo
add_executable(cmake-sticker ${CMAKE_SOURCE_DIR}/~logo/cmake-sticker.cc)
set_target_properties(cmake-sticker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake"
    OUTPUT_NAME "cmake-sticker"
)

# TODO: print logo, this should be implemented
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
message(STATUS "  -DRHINO8SDK_ROOT=...                           : Path to the Rhino 8 SDK root directory")
set(RHINO8SDK_ROOT "" CACHE PATH "")
message(STATUS "  -DRUN_POSTBUILD_RHINO=ON                       : Run Rhino just after the compilation (default: OFF)")
set(RUN_POSTBUILD_RHINO OFF CACHE BOOL "")
message(STATUS "  -DRHINO_EXE_PATH=...                           : Path to the Rhino executable (Rhino.exe) path directory")
set(RHINO_EXE_PATH "" CACHE PATH "")
message(STATUS "  -DENABLE_TESTS=ON                              : Enable tests (default: ON)")
set(ENABLE_TESTS ON CACHE BOOL "")
message(STATUS "========================================================================================================================")

# ----------------------------------------------------------------------------------------------------------------------------------------
# Source files, win resources and headers
# ----------------------------------------------------------------------------------------------------------------------------------------
project(${PLUGIN_NAME} LANGUAGES VERSION ${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH} CXX)

set(PLUGIN_CORE "${PLUGIN_NAME}_core")
set(PLUGIN_RHP "${PLUGIN_NAME}")
# set(PLUGIN_TESTS "${PLUGIN_NAME}_tests")  # TODO: maybe to be defined here


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

# set(BUILD_SHARED_LIBS TRUE)

add_library(${PLUGIN_CORE} STATIC)  # .lib

# FIXME: fix this part we need to differentiate between the plugin core and the plugin itself for src (there are entry points for plugin)
# file(GLOB_RECURSE PLUGIN_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
set(PLUGIN_SOURCES
    src/cmake4rhinoApp.cpp
    # src/cmake4rhinoPlugIn.cpp  # <-- this is the entry point of the .rhp plugin
    # src/cmdcmake4rhino.cpp
    src/stdafx.cpp
    src/CMake4Rhino/dummyLibFile.cpp
)


target_sources(${PLUGIN_CORE} PUBLIC
    ${PLUGIN_SOURCES}
)

# Rhino 8 SDK
find_package(Rhino8SDK REQUIRED)
target_link_libraries(${PLUGIN_CORE} PUBLIC RHINO_CORE_INTERFACE)



target_include_directories(${PLUGIN_CORE} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/CMake4Rhino  # FIXME: shouldd change it to CORE? check that the CMake4Rhnio directory is replaced by cookiecutter
)
target_precompile_headers(${PLUGIN_CORE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/stdafx.h)

# pre-processor data for the plugin
target_compile_definitions(${PLUGIN_CORE} PUBLIC
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



# # Change the .dll to .rhp so Rhino can load it
# add_library(${PLUGIN_RHP} SHARED)  # .dll (aka .rhp later)
# target_link_libraries(${PLUGIN_RHP} PRIVATE ${PLUGIN_CORE})
# set_target_properties(${PLUGIN_RHP} PROPERTIES SUFFIX ".rhp")
# set_target_properties(${PLUGIN_RHP} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
# )
# file(GLOB WIN32_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
#     ${PLUGIN_NAME}.rc
#     res/${PLUGIN_NAME}.rc
# )
# target_sources(${PLUGIN_RHP} PUBLIC
#     ${WIN32_RESOURCES}
# )

# ----------------------------------------------------------------------------------------------------------------------------------------
# >>> Insert additional dependencies and options >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
# ----------------------------------------------------------------------------------------------------------------------------------------
# Insert here your additional libraries or options (e.g., Boost, OpenCV, etc.)

# ----------------------------------------------------------------------------------------------------------------------------------------
# Basic dependencies and features
# ----------------------------------------------------------------------------------------------------------------------------------------




# ----------------------------------------------------------------------------------------------------------------------------------------
# Tests
# ----------------------------------------------------------------------------------------------------------------------------------------
if (ENABLE_TESTS)
    message(STATUS "Tests are enabled, adding test directory...")
    # add_subdirectory(tests)

    set(CMAKE_PLUGIN_TESTS "${PLUGIN_NAME}_tests")
    file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} tests/*.cpp)
    add_executable(${CMAKE_PLUGIN_TESTS} ${TEST_SOURCES})
    target_link_libraries(${CMAKE_PLUGIN_TESTS} PRIVATE
        ${PLUGIN_CORE}
    )
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


