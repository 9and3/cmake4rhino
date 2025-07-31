# FIXME: adapt for this subdirectory - out of update for now -


cmake_minimum_required(VERSION 3.15)
set(CMAKE_PLUGIN_TESTS "${PLUGIN_NAME}_tests")
project(${CMAKE_PLUGIN_TESTS} LANGUAGES CXX)



# Enable testing
# enable_testing()

# Add GoogleTest (recommended: use FetchContent for easy setup)
# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/heads/main.zip
# )
# # For Windows: prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # TODO: to inspect
# set(gtest_force_static ON CACHE BOOL "" FORCE)  # TODO: to inspect
# set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)  # Ensure static linking
# FetchContent_MakeAvailable(googletest)
# include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# add_executable(${CMAKE_PLUGIN_TESTS} $<TARGET_OBJECTS:PLUGIN_CORE> ${TEST_SOURCES})
add_executable(${CMAKE_PLUGIN_TESTS} ${TEST_SOURCES})

# target_sources(${CMAKE_PLUGIN_TESTS} PRIVATE
#     ../src/CMake4Rhino/dummyLibFile.cpp
# )

# # # Link with GoogleTest and your main library
target_link_libraries(${CMAKE_PLUGIN_TESTS}
    PRIVATE
    # gtest_main
    PLUGIN_CORE
    # RHINO_CORE_INTERFACE  # FIXME: this should not be here, we should import directly the plugin?
    # ${PLUGIN_NAME}  # FIXME: Creating big problems
)




# # Optionally include directories for mocks, etc.
# target_include_directories(${CMAKE_PLUGIN_TESTS} PRIVATE 
#   ${CMAKE_CURRENT_SOURCE_DIR}/../include
#   ${CMAKE_CURRENT_SOURCE_DIR}/../include/CMake4Rhino
# )
# target_precompile_headers(${CMAKE_PLUGIN_TESTS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stdafx.h)

# target_sources(${CMAKE_PLUGIN_TESTS} PRIVATE
#     ${PLUGIN_SOURCES}
#     ${WIN32_RESOURCES}
#     # Add more test files here as needed
# )

# target_precompile_headers(${CMAKE_PLUGIN_TESTS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include/stdafx.h)

# target_compile_definitions(${CMAKE_PLUGIN_TESTS} PUBLIC
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




# # Use GoogleTest's CMake integration for automatic test discovery
# gtest_discover_tests(${CMAKE_PLUGIN_TESTS})


# if (WIN32)
#     add_custom_command(
#         TARGET ${CMAKE_PLUGIN_TESTS} POST_BUILD
#         COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:${CMAKE_PLUGIN_TESTS}> $<TARGET_FILE_DIR:${CMAKE_PLUGIN_TESTS}>
#         COMMAND_EXPAND_LISTS
#     )
# endif ()



# # run tests after build
# message(STATUS "Running tests after build...")
# add_custom_target(run_tests ALL
#     COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose --output-on-failure
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     COMMENT "Running tests after build"
#     VERBATIM
# )