#include "stdafx.h"
#include "cmake4rhinoApp.h"
#include "CMake4Rhino/dummyLibFile.h"

#include <windows.h>
#include <iostream>

int main(int argc, char **argv) {
    ON_3dPoint center(0, 0, 0);
    std::cout << "ON_3dPoint center: (" << center.x << ", " << center.y << ", " << center.z << ")" << std::endl;
    ON_Sphere sphere = CMake4Rhino::DummyFunctions::DummySphere(5.0f);
    std::cout << "DummySphere test executed successfully." << std::endl;
    
    
    
    
    return 0;
}
