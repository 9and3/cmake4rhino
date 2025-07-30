// {{cookiecutter.your_plugin_name}}.h : main header file for the {{cookiecutter.your_plugin_name}} DLL.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h" // main symbols

// C{{cookiecutter.your_plugin_name}}App
// See {{cookiecutter.your_plugin_name}}App.cpp for the implementation of this class
//

class C{{cookiecutter.your_plugin_name}}App : public CWinApp
{
public:
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance construction belongs here. 
  // All other significant initialization should take place in
  // C{{cookiecutter.your_plugin_name}}PlugIn::OnLoadPlugIn().
	C{{cookiecutter.your_plugin_name}}App() = default;

  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance initialization belongs here. 
  // All other significant initialization should take place in
  // C{{cookiecutter.your_plugin_name}}PlugIn::OnLoadPlugIn().
	BOOL InitInstance() override;
  
  // CRITICAL: DO NOT CALL RHINO SDK FUNCTIONS HERE!
  // Only standard MFC DLL instance clean up belongs here. 
  // All other significant cleanup should take place in either
  // C{{cookiecutter.your_plugin_name}}PlugIn::OnSaveAllSettings() or
  // C{{cookiecutter.your_plugin_name}}PlugIn::OnUnloadPlugIn().  
	int ExitInstance() override;
  
	DECLARE_MESSAGE_MAP()
};
