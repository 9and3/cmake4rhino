message(STATUS "Tests are enabled, adding test directory...")

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_executable(${CMAKE_PLUGIN_TESTS} ${TEST_SOURCES})
target_link_libraries(${CMAKE_PLUGIN_TESTS} PRIVATE
    ${PLUGIN_CORE}
    gtest_main
    RHINO_CORE_INTERFACE
)

gtest_discover_tests(${CMAKE_PLUGIN_TESTS})

# FIXME: to solve, for now run the exe afterwards
# add_custom_command(TARGET ${CMAKE_PLUGIN_TESTS}
#     POST_BUILD
#     COMMAND $<TARGET_FILE:${CMAKE_PLUGIN_TESTS}>
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
# )