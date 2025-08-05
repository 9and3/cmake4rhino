message(STATUS "Tests are enabled, adding test directory...")

# we sue gtest as smain test framework
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_executable(${PLUGIN_TESTS} ${TEST_SOURCES})
target_sources(${PLUGIN_TESTS} PRIVATE
    ${PLUGIN_CORE_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/RhinoCore.cpp
)
target_link_libraries(${PLUGIN_TESTS} PRIVATE
    gtest_main
    RHINO_CORE_INTERFACE
    3RD_PARTY_LIBS
)
target_include_directories(${PLUGIN_TESTS} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# Rhino 8 SDK specific compilation flags for standalone (aka Rhino.Inside.Cpp)
target_precompile_headers(${PLUGIN_TESTS} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
target_compile_definitions(${PLUGIN_TESTS} PRIVATE $<$<CONFIG:Debug>:_DEBUG>)
# "/DELAYLOAD:opennurbs.dll" or "/DELAYLOAD:RhinoLibrary.dll" might needed in other standalone rh instances
target_link_options(${PLUGIN_TESTS} PRIVATE "/DELAYLOAD:RhinoCore.dll")

gtest_discover_tests(${PLUGIN_TESTS})

# to run the test after build
# add_custom_command(TARGET ${PLUGIN_TESTS}
#     POST_BUILD
#     COMMAND $<TARGET_FILE:${PLUGIN_TESTS}>
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
# )