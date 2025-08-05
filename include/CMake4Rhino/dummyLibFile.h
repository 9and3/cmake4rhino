#pragma once

// Use the following include guard for all files of your library that uses Rhino SDK
#ifdef RHINO_PLUGIN_BUILD
  #include "stdafx.h"
#else
  #include "pch.h"
#endif

namespace cmake4rhino
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
} // namespace cmake4rhino