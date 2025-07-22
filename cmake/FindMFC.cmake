include(FindPackageHandleStandardArgs)

set(MFC_FOUND FALSE)

# Only Microsoft Visual Studio generators support MFC
if(MSVC)
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        set(MFC_FOUND TRUE)
    endif()
endif()
if (MFC_FOUND)
    set(_MFC_HINTS
        "${MFC_ROOT}"
        "$ENV{MFC_ROOT}"
        "C:/Program Files (x86)/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC"
        "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC"
        "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Tools/MSVC"
    )
    find_path(MFC_INCLUDE_DIR
        NAMES afx.h
        PATH_SUFFIXES include
        HINTS ${_MFC_HINTS}
    )

    find_library(MFC_LIBRARY
        NAMES mfc140 mfc140u mfc140d mfc140ud
        HINTS ${_MFC_HINTS}
    )

    if(MFC_INCLUDE_DIR AND MFC_LIBRARY)
        set(MFC_FOUND TRUE)
    endif()
else()
    message(STATUS "MFC support is not enabled for this generator.")
endif()

find_package_handle_standard_args(MFC DEFAULT_MSG MFC_FOUND)

if(NOT MFC_FOUND)
    message(FATAL_ERROR "
        MFC was not found, please install Desktop development with via the Visual
        Studio Installer C++ MFC. Check for the -details- of the installer to enable
        MFC for newest build tools (86x, 64x)")
else()
    message(STATUS "MFC support enabled via Visual Studio generator.")
endif()