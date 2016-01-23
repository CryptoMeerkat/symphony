#pragma comment(lib, "SymphonyEngine.lib")

#include <iostream>
#include "../Engine/SymphonyEngine.h"

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

    engine->Run();
    
    engine->Release();

    return 0;
}