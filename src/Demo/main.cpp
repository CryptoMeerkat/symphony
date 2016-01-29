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
    
    PerspectiveCamera* camera = new PerspectiveCamera(Color::Grey(), 1.f, 1000.f, 45.f, Screen::AspectRatio());
    firstScene->AddGameObject(camera);
    firstScene->RegisterCamera(camera);
    t = camera->GetTransform();
    //t->Translate(glm::vec3(0.f, 0.f, 0.f));
    //t->Rotate(glm::vec3(0, 90.f, 0));
    
    GameObject* triangles[4];
    glm::vec4 colors[4]{ Color::Red(), Color::Green(), Color::Blue(), Color::Yellow() };
    for (size_t i = 0; i < 4; ++i)
    {
        triangles[i] = new GameObject();
        firstScene->AddGameObject(triangles[i]);
        
        triangles[i]->SetName("Triangle");
        triangles[i]->ModifyMeshRenderer(Mesh::Triangle(), Shader::GetDefaultShader(Shader::DefaultShaderName::UNLIT_COLOR));

        float x = 0, y = 0, rot = 0;
        switch (i)
        {
            case 0: x = 0; y = -5.f; rot = 0.f; break;
            case 1: x = -5.f; y = 0; rot = 270.f; break;
            case 2: x = 0; y = 5.f; rot = 180.f; break;
            case 3: x = 5.f; y = 0; rot = 90.f; break;
        }
        t = triangles[i]->GetTransform();
        t->Translate(glm::vec3(x, 0.f, y));
        t->Rotate(glm::vec3(0.f, rot, 0.f));

        auto mr = triangles[i]->GetMeshRenderer();
        mr->mesh->Colorize(colors[i]);
        /*glm::vec4 colors[3]{ Color::Red() , Color::Green(), Color::Blue() };
        mr->mesh->Colorize(colors, 3);*/
    }
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

    if (!engine->InitialiseWindow("Symphony: Test mode", 800, 600, false, true, false))
        return -1;

    LoadTestScene();
    
    engine->Run();
    
    //TO-DO: This could be set at the end of the engine lifecycle
    engine->Release();

    return 0;
}