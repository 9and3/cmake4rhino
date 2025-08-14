#include <gtest/gtest.h>

#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>

#include "pch.h"
#include "RhinoCore.h"

#include "fixture_rhinodoc.hh"

TEST_F(RhinoDocTest, T01_PluginIsInstalled) {
#ifdef PLUGIN_ID
    const wchar_t* pluginID_c = PLUGIN_ID;
    std::wstring pluginID_str = pluginID_c;

    ON_UUID pluginGUID = ON_UuidFromString(pluginID_str.c_str());
    CRhinoPlugInRecord* plugInRecord = nullptr;
    plugInRecord = CRhinoFileImportPlugIn::GetLoadedPlugIn(pluginGUID);
    
    ON_UUID pluginIDOnSystem;
    bool isSuc = plugInRecord->PlugInInfo().GetPlugInId(pluginIDOnSystem);
    char uuid_str[64] = {0};
    ON_UuidToString(pluginIDOnSystem, uuid_str);
    std::string pluginIDOnSystem_str = uuid_str;
    
    std::wstring pluginIDOnSystem_wstr(pluginIDOnSystem_str.begin(), pluginIDOnSystem_str.end());
    std::transform(pluginID_str.begin(), pluginID_str.end(), pluginID_str.begin(), ::towlower);
    std::transform(pluginIDOnSystem_wstr.begin(), pluginIDOnSystem_wstr.end(), pluginIDOnSystem_wstr.begin(), ::towlower);

    // Compare Rh plugin and the cmake plugin IDs to verify if installed
    ASSERT_EQ(pluginID_str, pluginIDOnSystem_wstr) << "The plugin is installed";
#else
    std::cout << "PLUGIN_ID is not defined. Skipping plugin installation test." << std::endl;
#endif
}