#include "Scene.h"

#include "Mouse.h"
#include "SymphonyEngine.h"

namespace Symphony
{
    Scene::Scene()
    {
        root = new GameObject();
        id = 0;
    }

    Scene::~Scene()
    {
        //TO-DO: recursively delete all GameObjects in this scene
        delete root;
    }

    void Scene::Update(float deltaTime)
    {
        //root->Update(deltaTime);
        
        if (SymphonyEngine::GetMouse()->ButtonClicked(Mouse::Button::LEFT))
            std::cout << "Left was clicked" << std::endl;
        if (SymphonyEngine::GetMouse()->ButtonClicked(Mouse::Button::MIDDLE))
            std::cout << "Middle was clicked" << std::endl;
        if (SymphonyEngine::GetMouse()->ButtonHold(Mouse::Button::RIGHT))
            std::cout << "Right is being hold" << std::endl;

        if (SymphonyEngine::GetKeyboard()->GetKeyDown(SDL_SCANCODE_SPACE))
        {
            std::cout << "Space pressed" << std::endl;
        }
        if (SymphonyEngine::GetKeyboard()->GetKeyUp(SDL_SCANCODE_SPACE))
        {
            std::cout << "Space lifted" << std::endl;
        }
        if (SymphonyEngine::GetKeyboard()->GetKeyUp(SDL_SCANCODE_N))
        {
            SymphonyEngine::Instance()->NextScene();
            return;
        }
    }

    void Scene::Render()
    {
        root->Render();
    }

    void Scene::AddGameObject(GameObject* newGameObject)
    {
        if (newGameObject)
        {
            root->AddChild(newGameObject);

            //TO-DO: Find a better way to represent the root node in the scenes
            newGameObject->SetParent(nullptr);
        }
    }
}