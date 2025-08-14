#include <gtest/gtest.h>

#include <windows.h>
#include <string>
#include <iostream>

#include "pch.h"
#include "RhinoCore.h"

#include "fixture_rhinodoc.hh"

TEST_F(RhinoDocTest, MyIntegrationTest) {
    // macro
    const wchar_t* cmdName = 
        L"!_cmake4rhino "
        L"\"test\" "
        L"_Enter";

    // run the command
    bool resCmd = pDoc->RunScript(cmdName);

    // get the objects added to the document
    ON_SimpleArray<ON_UUID> objectIDs = GetObjectIDs();

    ASSERT_TRUE(resCmd) << "Command execution failed";
    ASSERT_EQ(objectIDs.Count(), 2) << "No sphere and curve found in the document";
}