include(FindPackageHandleStandardArgs)

set(RHINO8SDK_FOUND FALSE)

# TODO: add a better help for hints?: RHINO8SDK_PATH can be defined or try the default location
set(_RHINO8SDK_HINTS
    "${RHINO8SDK_PATH}"
    "C:/Program Files/Rhino 8 SDK"
    "C:/Program Files (x86)/Rhino 8 SDK"
)

find_path(RHINO8SDK_INCLUDE_DIR
    NAMES RhinoSdk.h
    PATH_SUFFIXES inc
    HINTS ${_RHINO8SDK_HINTS}
)

find_path(RHINO8SDK_LIB_DIR
    NAMES RhinoCore.lib
    PATH_SUFFIXES lib/Release
    HINTS ${_RHINO8SDK_HINTS}
)

if(RHINO8SDK_INCLUDE_DIR AND RHINO8SDK_LIB_DIR)
    set(RHINO8SDK_FOUND TRUE)
endif()

# TODO: set all the library variables directly here

find_package_handle_standard_args(Rhino8SDK DEFAULT_MSG RHINO8SDK_INCLUDE_DIR RHINO8SDK_LIB_DIR)

if (NOT RHINO8SDK_FOUND)
    message(FATAL_ERROR "
        Rhino 8 SDK was not found, please install the Rhino 8 C++ SDK and set
        RHINO8SDK_PATH to the SDK installation path.")
else()
    message(STATUS "Rhino 8 SDK found: ${RHINO8SDK_INCLUDE_DIR}, ${RHINO8SDK_LIB_DIR}")
endif()