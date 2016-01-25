#pragma comment(lib, "SymphonyEngine.lib")

#include <iostream>
#include "glm/ext.hpp"
#include "../Engine/SymphonyEngine.h"
#include "../Engine/Transform.h"

using namespace Symphony;

SymphonyEngine* engine;

void LoadTestScene()
{
    Scene* firstScene = new Scene();
    engine->AddScene(firstScene);

    GameObject* triangle = new GameObject();
    triangle->SetName("Triangle");
    triangle->ModifyMeshRenderer(Mesh::Triangle(), Shader::GetDefaultShader(Shader::DefaultShaderName::UNLIT_COLOR));
    firstScene->AddGameObject(triangle);

    /*Transform go = Transform();
    std::cout << "Before: " << glm::to_string(go.Position()) << std::endl;
    go.SetPosition(glm::vec3(-1, -5, 500));
    go.Translate(glm::vec3(10, 1, 4));
    std::cout << "After: " << glm::to_string(go.Position()) << std::endl;*/
}

int main(int argc, char* args[])
{
    std::cout.setf(std::ios::boolalpha);

    engine = SymphonyEngine::Instance();
    
    if (!engine)
    {
        std::cerr << "Symphony Engine couldn't be created. The application will quit." << std::endl;
        return -1;
    }
    
    if (!engine->InitialiseWindow("Symphony: Test mode", 800, 600, false, true, true))
        return -1;
        
    LoadTestScene();
    
    engine->Run();
    
    //TO-DO: This could be set at the end of the engine lifecycle
    engine->Release();

    return 0;
}