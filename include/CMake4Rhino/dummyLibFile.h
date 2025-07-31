#pragma once

#include "stdafx.h"


namespace CMake4Rhino
{
  namespace DummyFunctions
  {
    /**
     * @brief This function is a placeholder to ensure that the dummyFile.cpp
     * is compiled and is testing correctly in the test suite.
     * It does not perform any particular operation.
     * 
     * @param radius The radius of the sphere, default is 1.0f.
     * @param center The center point of the sphere, default is ON_3dPoint::Origin().
     */
    ON_Sphere DummySphere(float radius = 1.0f, 
                          const ON_3dPoint& center = ON_3dPoint::Origin);
  } // namespace DummyFunctions
} // namespace CMake4Rhino