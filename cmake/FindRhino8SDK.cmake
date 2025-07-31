include(FindPackageHandleStandardArgs)

set(RHINO8SDK_FOUND FALSE)

set(_RHINO8SDK_HINTS
    "${RHINO8SDK_ROOT}"
    "C:/Program Files/Rhino 8 SDK"
    "C:/Program Files (x86)/Rhino 8 SDK"
    "C:/Program Files/Rhino 7 SDK"
    "C:/Program Files (x86)/Rhino 7 SDK"
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

find_package_handle_standard_args(Rhino8SDK DEFAULT_MSG RHINO8SDK_INCLUDE_DIR RHINO8SDK_LIB_DIR)

if (NOT RHINO8SDK_FOUND)
    message(FATAL_ERROR "
        Rhino 8 SDK was not found, please install the Rhino 8 C++ SDK and set
        DRHINO8SDK_ROOT to the SDK installation path.")
else()
    # Set an interface library for the Rhino SDK
    add_library(RHINO_CORE_INTERFACE INTERFACE)
    target_include_directories(RHINO_CORE_INTERFACE INTERFACE ${RHINO8SDK_INCLUDE_DIR})
    target_link_libraries(RHINO_CORE_INTERFACE INTERFACE
        ${RHINO8SDK_LIB_DIR}/RhinoCore.lib
        ${RHINO8SDK_LIB_DIR}/RhinoLibrary.lib
        ${RHINO8SDK_LIB_DIR}/rdk.lib
        ${RHINO8SDK_LIB_DIR}/opennurbs.lib
    )
    target_compile_definitions(RHINO_CORE_INTERFACE INTERFACE
        WIN64
        _WINDOWS
        _USRDLL
        _UNICODE
        UNICODE
        RHINO_LIB_DIR=${RHINO8SDK_LIB_DIR}
    )
    target_compile_options(RHINO_CORE_INTERFACE INTERFACE /UWIN32)  # Add this to undefine WIN64
    target_compile_definitions(RHINO_CORE_INTERFACE INTERFACE
        $<$<CONFIG:Debug>:_DEBUG;RHINO_DEBUG_PLUGIN>
    )
    target_compile_definitions(RHINO_CORE_INTERFACE INTERFACE
        $<$<CONFIG:Release>:NDEBUG>
    )

    message(STATUS "Rhino 8 SDK found: ${RHINO8SDK_INCLUDE_DIR}, ${RHINO8SDK_LIB_DIR}")
endif()