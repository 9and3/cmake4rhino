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
)

gtest_discover_tests(${CMAKE_PLUGIN_TESTS})

execute_process(
    COMMAND ${CMAKE_COMMAND} -E env "f:/cmake4rhino/build/tests/Debug/cmake4rhino_tests.exe"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    # RESULT_VARIABLE TEST_RESULT
    # OUTPUT_VARIABLE TEST_OUTPUT
    # ERROR_VARIABLE TEST_ERROR
)

# message(STATUS "Test process output:\n${TEST_OUTPUT}")
# message(STATUS "Test process error:\n${TEST_ERROR}")
# message(STATUS "Test process result: ${TEST_RESULT}")