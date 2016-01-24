#pragma comment(lib, "SymphonyEngine.lib")

#include "glm/ext.hpp"
#include <iostream>
#include "../Engine/SymphonyEngine.h"
#include "../Engine/Transform.h"

using namespace Symphony;

int main(int argc, char* args[])
{
    std::cout.setf(std::ios::boolalpha);

    SymphonyEngine* engine = SymphonyEngine::Instance();
    
    if (!engine)
    {
        std::cerr << "Symphony Engine couldn't be created. The application will quit." << std::endl;
        return -1;
    }

    if (!engine->InitialiseWindow("Symphony: Test mode", 1280, 768, false))
        return -1;

    if (SymphonyEngine::GetMouse()->ButtonClicked(Mouse::Button::LEFT))
        std::cout << "Left was clicked" << std::endl;

    Transform go = Transform();
    std::cout << "Before: " << glm::to_string(go.Position()) << std::endl;
    go.SetPosition(glm::vec3(-1, -5, 500));
    go.Translate(glm::vec3(10, 1, 4));
    std::cout << "After: " << glm::to_string(go.Position()) << std::endl;

    engine->Run();
    
    engine->Release();

    return 0;
}