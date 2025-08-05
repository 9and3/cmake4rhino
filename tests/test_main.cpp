#include <gtest/gtest.h>

#include "pch.h"
#include "RhinoCore.h"

int wmain(int argc, wchar_t** argv) {
    // initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // load Rhino
    // this will initialize the Rhino environment and allow us to use Rhino SDK functions
    CRhinoCore rhino_core(argc, argv);
    int ver = RhinoApp().ExeVersion();
    int sr = RhinoApp().ExeServiceRelease();
    ON_wString date;
    RhinoApp().GetBuildDate(date);
    std::wstring str0(static_cast<const wchar_t*>(date));
    std::wcout << "Rhino " << ver << "." << sr << " (" << str0 << ") loaded." << std::endl;

    return RUN_ALL_TESTS();
}