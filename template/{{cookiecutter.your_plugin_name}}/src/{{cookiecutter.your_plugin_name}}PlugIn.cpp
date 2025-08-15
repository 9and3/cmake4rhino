// {{cookiecutter.your_plugin_name}}PlugIn.cpp : defines the initialization routines for the plug-in.
//

#include "stdafx.h"
#include "rhinoSdkPlugInDeclare.h"
#include "{{cookiecutter.your_plugin_name}}PlugIn.h"
#include "Resource.h"

// The plug-in object must be constructed before any plug-in classes derived
// from CRhinoCommand. The #pragma init_seg(lib) ensures that this happens.
#pragma warning(push)
#pragma warning(disable : 4073)
#pragma init_seg(lib)
#pragma warning(pop)

// Rhino plug-in declaration
RHINO_PLUG_IN_DECLARE

// Rhino plug-in name
// Provide a short, friendly name for this plug-in.
RHINO_PLUG_IN_NAME(PLUGIN_NAME);

// Rhino plug-in id
// Provide a unique uuid for this plug-in.
RHINO_PLUG_IN_ID(PLUGIN_ID);

// Rhino plug-in version
// Provide a version number string for this plug-in.
RHINO_PLUG_IN_VERSION(PLUGIN_VERSION);

// Rhino plug-in description
// Provide a description of this plug-in.
RHINO_PLUG_IN_DESCRIPTION(PLUGIN_FILE_DESCRIPTION);

// Rhino plug-in icon resource id
// Provide an icon resource this plug-in.
// Icon resource should contain 16, 24, 32, 48, and 256-pixel image sizes.
RHINO_PLUG_IN_ICON_RESOURCE_ID(IDI_ICON);

// Rhino plug-in developer declarations taken from CMake variables, do not change
RHINO_PLUG_IN_DEVELOPER_ORGANIZATION(PLUGIN_COMPANY_NAME);
RHINO_PLUG_IN_DEVELOPER_ADDRESS(PLUGIN_ADDRESS);
RHINO_PLUG_IN_DEVELOPER_COUNTRY(PLUGIN_COUNTRY);
RHINO_PLUG_IN_DEVELOPER_PHONE(PLUGIN_PHONE);
RHINO_PLUG_IN_DEVELOPER_FAX(PLUGIN_FAX);
RHINO_PLUG_IN_DEVELOPER_EMAIL(PLUGIN_EMAIL);
RHINO_PLUG_IN_DEVELOPER_WEBSITE(PLUGIN_WEBSITE);
RHINO_PLUG_IN_UPDATE_URL(PLUGIN_UPDATE_URL);

// The one and only C{{cookiecutter.your_plugin_name}}PlugIn object
static class C{{cookiecutter.your_plugin_name}}PlugIn thePlugIn;

/////////////////////////////////////////////////////////////////////////////
// C{{cookiecutter.your_plugin_name}}PlugIn definition

C{{cookiecutter.your_plugin_name}}PlugIn& {{cookiecutter.your_plugin_name}}PlugIn()
{
	// Return a reference to the one and only C{{cookiecutter.your_plugin_name}}PlugIn object
	return thePlugIn;
}

C{{cookiecutter.your_plugin_name}}PlugIn::C{{cookiecutter.your_plugin_name}}PlugIn()
{
	// Description:
	//   C{{cookiecutter.your_plugin_name}}PlugIn constructor. The constructor is called when the
	//   plug-in is loaded and "thePlugIn" is constructed. Once the plug-in
	//   is loaded, C{{cookiecutter.your_plugin_name}}PlugIn::OnLoadPlugIn() is called. The
	//   constructor should be simple and solid. Do anything that might fail in
	//   C{{cookiecutter.your_plugin_name}}PlugIn::OnLoadPlugIn().

	// TODO: Add construction code here
	m_plugin_version = RhinoPlugInVersion();
}

/////////////////////////////////////////////////////////////////////////////
// Required overrides

const wchar_t* C{{cookiecutter.your_plugin_name}}PlugIn::PlugInName() const
{
	// Description:
	//   Plug-in name display string.  This name is displayed by Rhino when
	//   loading the plug-in, in the plug-in help menu, and in the Rhino
	//   interface for managing plug-ins.

	// TODO: Return a short, friendly name for the plug-in.
	return RhinoPlugInName();
}

const wchar_t* C{{cookiecutter.your_plugin_name}}PlugIn::PlugInVersion() const
{
	// Description:
	//   Plug-in version display string. This name is displayed by Rhino
	//   when loading the plug-in and in the Rhino interface for managing
	//   plug-ins.

	// TODO: Return the version number of the plug-in.
	return m_plugin_version;
}

GUID C{{cookiecutter.your_plugin_name}}PlugIn::PlugInID() const
{
	// Description:
	//   Plug-in unique identifier. The identifier is used by Rhino to
	//   manage the plug-ins.

	// TODO: Return a unique identifier for the plug-in.
	// {5AC5581C-0559-492F-9E46-21574EE7F52B}
	return ON_UuidFromString(RhinoPlugInId());
}

/////////////////////////////////////////////////////////////////////////////
// Additional overrides

BOOL C{{cookiecutter.your_plugin_name}}PlugIn::OnLoadPlugIn()
{
	// Description:
	//   Called after the plug-in is loaded and the constructor has been
	//   run. This is a good place to perform any significant initialization,
	//   license checking, and so on.  This function must return TRUE for
	//   the plug-in to continue to load.

	// Remarks:
	//    Plug-ins are not loaded until after Rhino is started and a default document
	//    is created.  Because the default document already exists
	//    CRhinoEventWatcher::On????Document() functions are not called for the default
	//    document.  If you need to do any document initialization/synchronization then
	//    override this function and do it here.  It is not necessary to call
	//    CPlugIn::OnLoadPlugIn() from your derived class.
	// TODO: Add plug-in initialization code here.

	return TRUE;
}

void C{{cookiecutter.your_plugin_name}}PlugIn::OnUnloadPlugIn()
{
	// Description:
	//    Called one time when plug-in is about to be unloaded. By this time,
	//    Rhino's mainframe window has been destroyed, and some of the SDK
	//    managers have been deleted. There is also no active document or active
	//    view at this time. Thus, you should only be manipulating your own objects.
	//    or tools here.

	// TODO: Add plug-in cleanup code here.
}



