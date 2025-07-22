// cmdcmake4rhino.cpp : command file
//

#include "stdafx.h"
#include "cmake4rhinoPlugIn.h"

// FIXME: this is a personal test code to print debug messages in the console
#include <windows.h>
#include <iostream>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN cmake4rhino command
//

#pragma region cmake4rhino command

// Do NOT put the definition of class CCommandDummyCmake4rhino in a header
// file. There is only ONE instance of a CCommandDummyCmake4rhino class
// and that instance is the static thecmake4rhinoCommand that appears
// immediately below the class definition.

class CCommandDummyCmake4rhino : public CRhinoCommand
{
public:
  // The one and only instance of CCommandDummyCmake4rhino is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandDummyCmake4rhino::CCommandDummyCmake4rhino()
  // is called exactly once when static thecmake4rhinoCommand is created.
  CCommandDummyCmake4rhino() = default;

  // CCommandDummyCmake4rhino::~CCommandDummyCmake4rhino()
  // is called exactly once when static thecmake4rhinoCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandDummyCmake4rhino() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {0CECE93D-3594-492B-8A29-4B9FB2AF6655}
    static const GUID cmake4rhinoCommand_UUID = 
    {0x0cece93d,0x3594,0x492b,{0x8a,0x29,0x4b,0x9f,0xb2,0xaf,0x66,0x55}};
    return cmake4rhinoCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"cmake4rhino"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandDummyCmake4rhino object
// Do NOT create any other instance of a CCommandDummyCmake4rhino class.
static class CCommandDummyCmake4rhino thecmake4rhinoCommand;

CRhinoCommand::result CCommandDummyCmake4rhino::RunCommand(const CRhinoCommandContext& context)
{
  // CCommandDummyCmake4rhino::RunCommand() is called when the user
  // runs the "cmake4rhino".

  // TODO: Add command code here.

  // Rhino command that display a dialog box interface should also support
  // a command-line, or script-able interface.
  ON_wString str;
  str.Format(L"The \"%s\" has been fired.\n", EnglishCommandName());
  const wchar_t* pszStr = static_cast<const wchar_t*>(str);
  if (context.IsInteractive())
    RhinoMessageBox(pszStr, cmake4rhinoPlugIn().PlugInName(), MB_OK);
  else
    RhinoApp().Print(pszStr);

  // print on console a simple debug message
#ifdef _DEBUG || RHINO_DEBUG_PLUGIN
  if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole())
  {
      freopen("CONOUT$", "w", stdout);
      std::cout << "Debug message from Rhino plug-in!" << std::endl;
  }
#else
  RhinoApp().Print(L"Debug message from Rhino plug-in (Rhino console)\n");
#endif


  // add a simple curve circle to test geometries
  ON_3dPoint center(0, 0, 0);
  double radius = 10.0;
  ON_Circle circle( center, radius );
  ON_ArcCurve arc_curve( circle );
  CRhinoCurveObject* curve_object = context.m_doc.AddCurveObject( arc_curve );
  context.m_doc.Redraw();


  // TODO: Return one of the following values:
  //   CRhinoCommand::success:  The command worked.
  //   CRhinoCommand::failure:  The command failed because of invalid input, inability
  //                            to compute the desired result, or some other reason
  //                            computation reason.
  //   CRhinoCommand::cancel:   The user interactively canceled the command 
  //                            (by pressing ESCAPE, clicking a CANCEL button, etc.)
  //                            in a Get operation, dialog, time consuming computation, etc.

  return CRhinoCommand::success;
}

#pragma endregion

//
// END cmake4rhino command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
