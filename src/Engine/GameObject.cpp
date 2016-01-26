#include "GameObject.h"
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include "SymphonyEngine.h"
//TO-DO: <algorithm> is required for the correct use of std::remove used in RemoveChild;
//       find a way to avoid using this.
//#include <algorithm>

namespace Symphony
{
    GameObject::GameObject()
    {
        parent = nullptr;
        meshRenderer = nullptr;
        name = "New GameObject";
        isEnabled = true;
    }

    GameObject::GameObject(Transform & t)
        : GameObject()
    {
        transform = t;

    }

    GameObject::~GameObject()
    {
        delete meshRenderer;
    }

    void GameObject::ModifyMeshRenderer(Mesh* newMesh, Shader* newShader)
    {
        if (meshRenderer)
        {
            meshRenderer->mesh = newMesh;
            meshRenderer->shader = newShader;
            return;
        }
        
        meshRenderer = new MeshRenderer(newMesh, newShader);
    }

    void GameObject::Update(float deltaTime)
    {
        if (parent)
            transform.UpdateWorldMatrix(parent->transform.GetWorldMatrix());
        else
            transform.UpdateWorldMatrix();

        if (meshRenderer && meshRenderer->OkToRender())
        {
            if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_RIGHT))
            {
                glm::vec3 r = glm::vec3(0, 45, 0) * deltaTime;
                transform.Rotate(r);
            }
            else if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_LEFT))
            {
                glm::vec3 r = glm::vec3(0, -45, 0) * deltaTime;
                transform.Rotate(r);
            }
            if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_UP))
            {
                glm::vec3 r = glm::vec3(45, 0, 0) * deltaTime;
                transform.Rotate(r);
            }
            else if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_DOWN))
            {
                glm::vec3 r = glm::vec3(-45, 0, 0) * deltaTime;
                transform.Rotate(r);
            }
            if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_LCTRL))
            {
                glm::vec3 r = glm::vec3(0, 0, 45) * deltaTime;
                transform.Rotate(r);
            }
            else if (SymphonyEngine::GetKeyboard()->GetKeyHold(SDL_SCANCODE_RCTRL))
            {
                glm::vec3 r = glm::vec3(0, 0, -45) * deltaTime;
                transform.Rotate(r);
            }
        }

        std::cout << std::endl << "Object: " << name << std::endl << transform << std::endl;

        for (GameObject* go : children)
        {
            if (go->isEnabled)
                go->Update(deltaTime);
        }
    }
    
    void GameObject::Render()
    {
        if (meshRenderer && meshRenderer->OkToRender())
        {
            (*meshRenderer->shader).Use();
            glm::mat4 identity;

            glUniformMatrix4fv((*meshRenderer->shader)("viewMatrix"), 1, GL_FALSE, glm::value_ptr(identity));
            glUniformMatrix4fv((*meshRenderer->shader)("projMatrix"), 1, GL_FALSE, glm::value_ptr(identity));

            glUniformMatrix4fv((*meshRenderer->shader)("modelMatrix"), 1, GL_FALSE, glm::value_ptr(transform.GetWorldMatrix()));
            meshRenderer->Render();
            (*meshRenderer->shader).Release();
        }

        for (GameObject* go : children)
        {
            if (go->isEnabled)
                go->Render();
        }
    }

    /*void GameObject::RemoveChild(GameObject* c)
    {
        children.erase(std::remove(children.begin(), children.end(), c), children.end());
    }*/
}

