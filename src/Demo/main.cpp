#pragma comment(lib, "SymphonyEngine.lib")

#include <iostream>
//#include "glm/ext.hpp"
#include "../Engine/SymphonyEngine.h"
#include "../Engine/PerspectiveCamera.h"
#include "../Engine/Color.h"

using namespace Symphony;

SymphonyEngine* engine;

void LoadTestScene()
{
    Scene* firstScene = new Scene();
    engine->AddScene(firstScene);

    Transform* t = nullptr;
    
    PerspectiveCamera* camera = new PerspectiveCamera(Color::Red(), 1.f, 1000.f, 45.f, Screen::AspectRatio());
    firstScene->AddGameObject(camera);
    firstScene->RegisterCamera(camera);
    t = camera->GetTransform();
    t->SetRotation(glm::vec3(0, 180.f, 0));

    GameObject* triangle = new GameObject();
    firstScene->AddGameObject(triangle);
    
    triangle->SetName("Triangle");
    triangle->ModifyMeshRenderer(Mesh::Triangle(), Shader::GetDefaultShader(Shader::DefaultShaderName::UNLIT_COLOR));
    
    t = triangle->GetTransform();
    t->Translate(glm::vec3(0.f, 0, 3.f));

    auto mr = triangle->GetMeshRenderer();
    mr->mesh->Colorize(Color::Yellow());
    glm::vec4 colors[3]{ Color::Red() , Color::Green() ,Color::Blue() };
    mr->mesh->Colorize(colors, 3);
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