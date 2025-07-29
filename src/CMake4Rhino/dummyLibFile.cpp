#include "CMake4Rhino/dummyLibFile.h"


namespace CMake4Rhino
{
  namespace DummyFunctions
  {
    ON_Sphere DummySphere(float radius,
                          const ON_3dPoint& center)
    {
      ON_Sphere sphere(center, radius);
      return sphere;
    }
  } // namespace DummyFunctions
} // namespace CMake4Rhino