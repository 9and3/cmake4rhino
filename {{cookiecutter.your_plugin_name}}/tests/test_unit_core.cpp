#include <gtest/gtest.h>

// #include "stdafx.h"
#include "pch.h"
#include "core/dummyLibFile.h"

// This is a simple test case to verify the use of Rhino SDK types and functions
TEST(TEST_UNIT_RhinoTestSuite, TDPointTest) {
    ON_3dPoint center(0, 1, 2);
    EXPECT_EQ(center.x, 0);
    EXPECT_EQ(center.y, 1);
    EXPECT_EQ(center.z, 2);
}

// This is a test to check personal library associated to the plugin
TEST(TEST_UNIT_CoreLibTestSuite, FunctionDummySphereTest) {
    float expected_radius = 5.0f;
    ON_Sphere sphere = {{cookiecutter.your_plugin_name}}::DummyFunctions::DummySphere(expected_radius);
    EXPECT_FLOAT_EQ(sphere.Radius(), expected_radius);
}


