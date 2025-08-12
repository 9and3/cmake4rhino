#include <gtest/gtest.h>

#include <windows.h>
#include <string>
#include <iostream>

#include "pch.h"
#include "RhinoCore.h"

/**
 * @brief This is the  fixture to open and clean automatically a Rhino document.
 * You can add here all functionalities linked to the document.
 * 
 */
class RhinoDocTest : public ::testing::Test {
protected:
    int doc_runtime_serial_number = 0;
    CRhinoDoc* pDoc = nullptr;

    void SetUp() override {
        CRhinoCreateDocumentOptions options;
        options.SetCreateHeadless(false);  // if true, RunScript will not work properly with geometries
        doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
        pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);
        ASSERT_TRUE(pDoc != nullptr);
    }

    void TearDown() override {
        if (pDoc && doc_runtime_serial_number)
            pDoc->CloseDocument(doc_runtime_serial_number);

        m_objectIDs.Empty();
    }

    ON_SimpleArray<ON_UUID> GetObjectIDs() {
        CRhinoObjectIterator it(*pDoc, CRhinoObjectIterator::normal_objects);
        while (const CRhinoObject* pObject = it.Next()) {
            m_objectIDs.Append(pObject->Id());
        }
        return m_objectIDs;
    }

private:
    ON_SimpleArray<ON_UUID> m_objectIDs;

};

/**
 * @brief This is an example integration test for the Rhino document.
 * Use macros to make it run and read/modify and evaluate the added geometries
 * to make your assertions.
 *
 */
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