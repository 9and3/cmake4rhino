
/*
This is a test to integrate the running of the commands from the plugin cmake4rhino. Test it in a running Rhino instance (possibly
headless) to see if the commandd works as expectedd.
--> cmake should snure that the executable Rhino is found
--> how to check the results in a systematicx way? Use the Rhino console or a log file? 
--> it shouldd be controleddd by Google test framework (e.g. fixtures etc.)

--> we need to run the command in rhinocode.exe and see if it works as expected. Now the question is how to see if the 
producedd ressults is as expected?
*/


#include <gtest/gtest.h>

// Rhino SDK classes
// #include "stdafx.h"
#include "RhinoSdk.h"

// // Rhino Render Development Kit (RDK) classes
// #include "RhRdkHeaders.h" 

#include "RhinoSdkDoc.h"             // For CRhinoDoc
#include "RhinoSdkFileUtilities.h"   // For CRhinoFileUtilities


static unsigned int RhOpenHeadlessDocument(const wchar_t* pszPath)
{
  if (nullptr == pszPath || 0 == pszPath[0])
    return 0;

//   if (!CRhinoFileUtilities::FileExists(pszPath))
//     return 0;

//   CRhinoOpenDocumentOptions options;
//   options.SetCreateHeadless(true);
//   options.SetMakeVisible(false);
//   options.SetAddToMRU(false);
//   options.SetUpdateDefaultDirectory(false);
//   options.SetUserQueriesPermitted(false);
//   options.SetFileReadingPlugInId(ON_nil_uuid, 0);

//   return CRhinoDoc::OpenDocument(pszPath, &options);
  return 0;
}

TEST(TEST_UNIT_RhissssnoTestSuite, TDPoissssntTest) {
    
    const wchar_t* model_path = L"test_model.3dm";
    unsigned int doc_sn = RhOpenHeadlessDocument(model_path);
    
    
    ON_3dPoint center(0, 1, 2);



    EXPECT_EQ(center.x, 0);
    EXPECT_EQ(center.y, 1);
    EXPECT_EQ(center.z, 2);
}

TEST(DUMMY_TEsssST, DummsssyTest)
{
    // This is a dummy test to ensure the test framework is set up correctly.
    EXPECT_TRUE(true);
}

