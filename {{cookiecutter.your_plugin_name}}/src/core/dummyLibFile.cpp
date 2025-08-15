


#include "core/dummyLibFile.h"



namespace {{cookiecutter.your_plugin_name}}
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
} // namespace {{cookiecutter.your_plugin_name}}