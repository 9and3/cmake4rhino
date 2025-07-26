include(FindPackageHandleStandardArgs)

set(_RHINO_EXE_HINTS
    "${RHINO_EXE_PATH}"
    "C:/Program Files/Rhino 8/System"
    "C:/Program Files/Rhino 8"
    "C:/Program Files (x86)/Rhino 8/System"
    "C:/Program Files (x86)/Rhino 8"
    "C:/Program Files/Rhino 7/System"
    "C:/Program Files/Rhino 7"
    "C:/Program Files (x86)/Rhino 7/System"
    "C:/Program Files (x86)/Rhino 7"
)

# Try to find Rhino 8 first, then Rhino 7
find_program(RHINO_EXE
    NAMES Rhino.exe
    HINTS ${_RHINO_EXE_HINTS}
)

find_package_handle_standard_args(RhinoExe DEFAULT_MSG RHINO_EXE)

if(NOT RHINO_EXE)
    message(FATAL_ERROR "
        Rhino.exe was not found. Please install Rhino 8 or 7 and/or set RHINO_EXE_PATH to the installation path (e.g., C:/Program Files/Rhino 8/System).")
else()
    message(STATUS "Rhino executable found: ${RHINO_EXE}")
endif()