#include <gtest/gtest.h>

#include <windows.h>
#include <string>
#include <iostream>

#include "pch.h"
#include "RhinoCore.h"

TEST(TEST_SMOKE_PluginManagement, PluginInstalled) {
    // CRhinoCore rhino_core();

    CRhinoCreateDocumentOptions options;
    options.SetCreateHeadless(true);  // if true, RunScript will not work properly with geometries
    int doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
    CRhinoDoc* pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);

    // create UUID to import from the guid string
    std::string guid = "5AC5581C-0559-492F-9E46-21574EE7F52B";
    ON_UUID pluginGUID = ON_UuidFromString(guid.c_str());
    CRhinoPlugInRecord* plugInRecord = nullptr;
    plugInRecord = CRhinoFileImportPlugIn::GetLoadedPlugIn(pluginGUID);


    ON_UUID PlugInID_read;
    bool isSuc = plugInRecord->PlugInInfo().GetPlugInId(PlugInID_read);
    char uuid_str[64] = {0};
    ON_UuidToString(PlugInID_read, uuid_str);
    std::string PlugInID_read_str = uuid_str;

    std::cout << "PlugInID_read: " << PlugInID_read_str << std::endl;
    // std::wcout << "read info" << plugInRecord->PlugInInfo().PlugInPath() << std::endl;

    // ASSERT_NE(plugInRecord, nullptr);
    // ASSERT_TRUE(false);

    // make an assertion that needs to fail
    ASSERT_TRUE(false);
}