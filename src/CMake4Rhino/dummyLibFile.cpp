#include "cmake4rhino/dummyLibFile.h"


namespace cmake4rhino
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
} // namespace cmake4rhino