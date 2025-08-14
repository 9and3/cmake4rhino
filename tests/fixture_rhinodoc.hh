#include <gtest/gtest.h>

#include "pch.h"
#include "RhinoCore.h"


class RhinoDocTest : public ::testing::Test {
protected:
    int doc_runtime_serial_number = 0;
    CRhinoDoc* pDoc = nullptr;

    void SetUp() override {
        CRhinoCreateDocumentOptions options;
        options.SetCreateHeadless(false);  // if true, RunScript will not work properly with geometries
        doc_runtime_serial_number = CRhinoDoc::CreateDocument(nullptr, &options);
        pDoc = CRhinoDoc::FromRuntimeSerialNumber(doc_runtime_serial_number);
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