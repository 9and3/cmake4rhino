include(FindPackageHandleStandardArgs)

set(RHINO8SDK_FOUND FALSE)

set(_RHINO8SDK_HINTS
    "${RHINOSDK_ROOT}"
    "C:/Program Files/Rhino 8 SDK"
    "C:/Program Files (x86)/Rhino 8 SDK"
    "C:/Program Files/Rhino 7 SDK"
    "C:/Program Files (x86)/Rhino 7 SDK"
)

find_path(RHINOSDK_INCLUDE_DIR
    NAMES RhinoSdk.h
    PATH_SUFFIXES inc
    HINTS ${_RHINO8SDK_HINTS}
)

find_path(RHINOSDK_LIB_DIR
    NAMES RhinoCore.lib
    PATH_SUFFIXES lib/Release
    HINTS ${_RHINO8SDK_HINTS}
)
find_path(RHINOSDK_ONURBS_INCLUDE_DIR
    NAMES opennurbs.h
    PATH_SUFFIXES openNURBS
    HINTS ${_RHINO8SDK_HINTS}
)

if(RHINOSDK_INCLUDE_DIR AND RHINOSDK_LIB_DIR)
    set(RHINO8SDK_FOUND TRUE)
endif()

find_package_handle_standard_args(Rhino8SDK DEFAULT_MSG RHINOSDK_INCLUDE_DIR RHINOSDK_LIB_DIR)

if (NOT RHINO8SDK_FOUND)
    message(FATAL_ERROR "
        Rhino 8 SDK was not found, please install the Rhino 8 C++ SDK and set
        DRHINOSDK_ROOT to the SDK installation path.")
else()
    # Set an interface library for the Rhino SDK
    add_library(RHINO_CORE_INTERFACE INTERFACE)
    target_link_libraries(RHINO_CORE_INTERFACE INTERFACE
    ${RHINOSDK_LIB_DIR}/RhinoCore.lib
    ${RHINOSDK_LIB_DIR}/RhinoLibrary.lib
    ${RHINOSDK_LIB_DIR}/rdk.lib
    ${RHINOSDK_LIB_DIR}/opennurbs.lib
    )
    target_compile_definitions(RHINO_CORE_INTERFACE INTERFACE
        ON_RUNTIME_WIN
        WIN64
        _WINDOWS
        _USRDLL
        _UNICODE
        UNICODE
        RHINO_LIB_DIR=${RHINOSDK_LIB_DIR}

        $<$<CONFIG:Debug>:_DEBUG;RHINO_DEBUG_PLUGIN>
        $<$<CONFIG:Release>:NDEBUG>
    )
    target_compile_options(RHINO_CORE_INTERFACE INTERFACE /UWIN32)  # Add this to undefine WIN64
    target_include_directories(RHINO_CORE_INTERFACE INTERFACE
        ${RHINOSDK_INCLUDE_DIR}
        ${RHINOSDK_ONURBS_INCLUDE_DIR}
    )

    message(STATUS "Rhino 8 SDK found: ${RHINOSDK_INCLUDE_DIR}, ${RHINOSDK_LIB_DIR}")
    message(STATUS "Rhino 8 SDK OpenNURBS include directory: ${RHINOSDK_ONURBS_INCLUDE_DIR}")
endif()