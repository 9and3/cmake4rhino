#include <gtest/gtest.h>

TEST(DUMMY_TEST, DummyTest)
{
    // This is a dummy test to ensure the test framework is set up correctly.
    EXPECT_TRUE(true);
}

// #include "stdafx.h"
// #include "cmake4rhino/dummyLibFile.h"

// // This is a simple test case to verify the use of Rhino SDK types and functions
// TEST(TEST_UNIT_RhinoTestSuite, TDPointTest) {
//     ON_3dPoint center(0, 1, 2);
//     EXPECT_EQ(center.x, 0);
//     EXPECT_EQ(center.y, 1);
//     EXPECT_EQ(center.z, 2);
// }

// // This is a test to check personal library associated to the plugin
// TEST(TEST_UNIT_CoreLibTestSuite, FunctionDummySphereTest) {
//     float expected_radius = 5.0f;
//     ON_Sphere sphere = cmake4rhino::DummyFunctions::DummySphere(expected_radius);
//     EXPECT_FLOAT_EQ(sphere.Radius(), expected_radius);
// }


