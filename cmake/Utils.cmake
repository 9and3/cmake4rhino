# Splits a list of source files into two lists based on whether they include any of the specified headers.
# Usage:
#   find_sources_with_includes(
#     SOURCES <list of files>
#     INCLUDES <list of header names>
#     out_with <output variable for files with includes>
#     out_without <output variable for files without includes>
#   )
function(find_sources_with_includes)
    set(options)
    set(oneValueArgs out_with out_without)
    set(multiValueArgs SOURCES INCLUDES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(with_includes)
    set(without_includes)

    foreach(src ${ARG_SOURCES})
        file(READ "${src}" file_content)
        set(has_include FALSE)
        foreach(inc ${ARG_INCLUDES})
            string(REGEX MATCH "#[ \t]*include[ \t]*[<\"]${inc}[\">]" match "${file_content}")
            if(match)
                set(has_include TRUE)
                break()
            endif()
        endforeach()
        if(has_include)
            list(APPEND with_includes "${src}")
        else()
            list(APPEND without_includes "${src}")
        endif()
    endforeach()

    set(${ARG_out_with} "${with_includes}" PARENT_SCOPE)
    set(${ARG_out_without} "${without_includes}" PARENT_SCOPE)
endfunction()

# Prints each item in a list variable on a new line, with an optional header.
# Usage:
#   recursive_print(<list_var> HEADER "Optional header")
function(recursive_print list_var)
    set(options)
    set(oneValueArgs HEADER)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARG_HEADER)
        message(STATUS "${ARG_HEADER}")
    endif()

    foreach(item ${${list_var}})
        message(STATUS ">  ${item}")
    endforeach()
endfunction()