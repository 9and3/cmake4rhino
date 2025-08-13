#include <gtest/gtest.h>

// #include <windows.h>
// #include <shlobj.h>     // SHGetKnownFolderPath
// #include <combaseapi.h> // CoTaskMemFree
// #include <string>
// #include <algorithm>
// #include <filesystem>
// #include <iostream>

#include "pch.h"
#include "RhinoCore.h"

// // Check-in stallation check
// bool DirectoryExists(const std::string& path) {
//     return std::filesystem::exists(path) && std::filesystem::is_directory(path);
// }
// std::string GetFolderPath(REFKNOWNFOLDERID folderId) {
//     PWSTR path = nullptr;
//     std::string result;
//     if (SUCCEEDED(SHGetKnownFolderPath(folderId, 0, NULL, &path))) {
//         char charPath[MAX_PATH];
//         wcstombs(charPath, path, MAX_PATH);
//         CoTaskMemFree(path);
//         result = charPath;
//     }
//     return result;
// }
// bool RegistryKeyExists(HKEY root, const std::string& subKey, REGSAM viewFlags) {
//     HKEY hKey;
//     LONG res = RegOpenKeyExA(root, subKey.c_str(), 0, KEY_READ | viewFlags, &hKey);
//     if (res == ERROR_SUCCESS) {
//         RegCloseKey(hKey);
//         return true;
//     }
//     return false;
// }
// bool IsPluginInstalled(const std::string& guid, int majorVersion) {
//     // Lowercase GUID
//     std::string guidLower = guid;
//     std::transform(guidLower.begin(), guidLower.end(), guidLower.begin(), ::tolower);

//     // Registry paths to check
//     std::string regBase = "SOFTWARE\\McNeel\\Rhinoceros\\" + std::to_string(majorVersion) + ".0\\Plug-ins\\";
//     std::string regPaths[] = {
//         regBase + guid,
//         regBase + guidLower
//     };

//     // Registry hives and views
//     HKEY roots[] = { HKEY_LOCAL_MACHINE, HKEY_CURRENT_USER };
//     REGSAM views[] = { KEY_WOW64_64KEY, KEY_WOW64_32KEY };

//     for (auto root : roots) {
//         for (auto view : views) {
//             for (auto& path : regPaths) {
//                 if (RegistryKeyExists(root, path, view)) {
//                     return true;
//                 }
//             }
//         }
//     }

//     // Folder locations
//     std::string appdata = GetFolderPath(FOLDERID_RoamingAppData);
//     std::string programdata = GetFolderPath(FOLDERID_ProgramData);

//     std::string baseAppdata = appdata + "\\McNeel\\Rhinoceros\\" + std::to_string(majorVersion) + ".0\\Plug-ins\\";
//     std::string baseProgramdata = programdata + "\\McNeel\\Rhinoceros\\" + std::to_string(majorVersion) + ".0\\Plug-ins\\";

//     std::string folderPaths[] = {
//         baseAppdata + guid,
//         baseAppdata + guidLower,
//         baseProgramdata + guid,
//         baseProgramdata + guidLower
//     };

//     for (auto& p : folderPaths) {
//         if (DirectoryExists(p)) {
//             return true;
//         }
//     }

//     return false;
// }


int wmain(int argc, wchar_t** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // try {
    //     CRhinoCore rhino_core(argc, argv);
    //     int ver = RhinoApp().ExeVersion();
    //     int sr = RhinoApp().ExeServiceRelease();
    //     ON_wString date;
    //     RhinoApp().GetBuildDate(date);
    //     std::wstring str0(static_cast<const wchar_t*>(date));
    //     std::wcout << "Rhino " << ver << "." << sr << " (" << str0 << ") loaded." << std::endl;

    //     CRhinoCreateDocumentOptions options;
    //     options.SetCreateHeadless(false);  // if true, RunScript will not work properly with geometries
    //     int doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
    //     CRhinoDoc* pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);

    // } catch (const std::exception& e) {
    //     std::cerr << "Error initializing RhinoCore: " << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }



    CRhinoCore rhino_core(argc, argv);
    int ver = RhinoApp().ExeVersion();
    int sr = RhinoApp().ExeServiceRelease();
    ON_wString date;
    RhinoApp().GetBuildDate(date);
    std::wstring str0(static_cast<const wchar_t*>(date));
    std::wcout << "Rhino " << ver << "." << sr << " (" << str0 << ") loaded." << std::endl;

    // CRhinoCreateDocumentOptions options;
    // options.SetCreateHeadless(false);  // if true, RunScript will not work properly with geometries
    // int doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
    // CRhinoDoc* pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);


    // std::string guid = "5AC5581C-0559-492F-9E46-21574EE7F52B";
    // int rhinoVersion = 8;

    // if (IsPluginInstalled(guid, rhinoVersion)) {
    //     std::cout << "Plugin is installed." << std::endl;
    // } else {
    //     std::cout << "Plugin is NOT installed." << std::endl;
    // }
    // return 0;



    // CRhinoCreateDocumentOptions options;
    // options.SetCreateHeadless(true);  // if true, RunScript will not work properly with geometries
    // int doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
    // CRhinoDoc* pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);

    // // create UUID to import from the guid string
    // ON_UUID pluginGUID = ON_UuidFromString(guid.c_str());
    // CRhinoPlugInRecord* plugInRecord = nullptr;
    // plugInRecord = CRhinoFileImportPlugIn::GetLoadedPlugIn(pluginGUID);
    // // pDoc->ReadPlugInFile("5AC5581C-0559-492F-9E46-21574EE7F52B");


    // CRhinoCore rhino_core();

    // int ver = RhinoApp().ExeVersion();
    // int sr = RhinoApp().ExeServiceRelease();
    // ON_wString date;
    // RhinoApp().GetBuildDate(date);
    // std::wstring str0(static_cast<const wchar_t*>(date));
    // std::cout << "Rhino " << ver << "." << sr << std::endl;




    
    return RUN_ALL_TESTS();
}