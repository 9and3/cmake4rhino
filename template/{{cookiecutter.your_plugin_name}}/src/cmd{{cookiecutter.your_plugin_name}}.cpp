// cmd{{cookiecutter.your_plugin_name}}.cpp : command file
//

#include "stdafx.h"
#include "{{cookiecutter.your_plugin_name}}PlugIn.h"

// Include any cusstom libraries or your own headers here
#include "core/dummyLibFile.h"

// This is a personal test code to print debug messages in the console
#include <windows.h>
#include <iostream>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN {{cookiecutter.your_plugin_name}} command
//

#pragma region {{cookiecutter.your_plugin_name}} command

// Do NOT put the definition of class CCommand{{cookiecutter.your_plugin_name}} in a header
// file. There is only ONE instance of a CCommand{{cookiecutter.your_plugin_name}} class
// and that instance is the static the{{cookiecutter.your_plugin_name}}Command that appears
// immediately below the class definition.

class CCommand{{cookiecutter.your_plugin_name}} : public CRhinoCommand
{
public:
  // The one and only instance of CCommand{{cookiecutter.your_plugin_name}} is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommand{{cookiecutter.your_plugin_name}}::CCommand{{cookiecutter.your_plugin_name}}()
  // is called exactly once when static the{{cookiecutter.your_plugin_name}}Command is created.
  CCommand{{cookiecutter.your_plugin_name}}() = default;

  // CCommand{{cookiecutter.your_plugin_name}}::~CCommand{{cookiecutter.your_plugin_name}}()
  // is called exactly once when static the{{cookiecutter.your_plugin_name}}Command is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommand{{cookiecutter.your_plugin_name}}() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {0CECE93D-3594-492B-8A29-4B9FB2AF6655}
    static const GUID {{cookiecutter.your_plugin_name}}Command_UUID = 
    {0x0cece93d,0x3594,0x492b,{0x8a,0x29,0x4b,0x9f,0xb2,0xaf,0x66,0x55}};
    return {{cookiecutter.your_plugin_name}}Command_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"{{cookiecutter.your_plugin_name}}"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommand{{cookiecutter.your_plugin_name}} object
// Do NOT create any other instance of a CCommand{{cookiecutter.your_plugin_name}} class.
static class CCommand{{cookiecutter.your_plugin_name}} the{{cookiecutter.your_plugin_name}}Command;

// TODO: Add command code here.
CRhinoCommand::result CCommand{{cookiecutter.your_plugin_name}}::RunCommand(const CRhinoCommandContext& context)
{
  CRhinoDoc* doc = context.Document();
  if (nullptr == doc)
    return CRhinoCommand::failure;

  // print on console a simple debug message
#ifdef RHINO_DEBUG_PLUGIN
  std::cout << "Debug-mode message from Rhino plug-in (Win console)\n" << std::endl;
  RhinoApp().Print(L"Debug-mode message from Rhino plug-in (Rhino console)\n");
#else
  RhinoApp().Print(L"Release-mode message from Rhino plug-in (Rhino console)\n");
#endif

  // FIXME: see integration with cookiecutter
  // Call a function from the dummy library to test if it works
  ON_Sphere sphere = {{cookiecutter.your_plugin_name}}::DummyFunctions::DummySphere(5.0f);
  ON_Brep* pBrep = ON_BrepSphere(sphere);
  CRhinoBrepObject* brep_object = context.m_doc.AddBrepObject(*pBrep);
  context.m_doc.Redraw();

  // Prompt for a block to insert
  CRhinoGetString gs;
  gs.SetCommandPrompt(L"Testing input");
  gs.GetString();
  if (gs.CommandResult() != CRhinoCommand::success)
    return gs.CommandResult();
  ON_wString block_name = gs.String();
  block_name.TrimLeftAndRight();
  if (block_name.IsEmpty())
    return CRhinoCommand::cancel;

  // add a simple curve circle to test geometries
  ON_3dPoint center(0, 0, 0);
  double radius = 10.0;
  ON_Circle circle( center, radius );
  ON_ArcCurve arc_curve( circle );
  CRhinoCurveObject* curve_object = context.m_doc.AddCurveObject(arc_curve);
  context.m_doc.Redraw();

  // ask the user to click the point
  

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
// END {{cookiecutter.your_plugin_name}} command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
