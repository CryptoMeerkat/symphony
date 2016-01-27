#pragma once

#include <vector>
#include "GameObject.h"
#include "Camera.h"

namespace Symphony
{
    class Scene
    {
        friend class SymphonyEngine;
        
    public:
        //TO-DO: Perhaps the constructors and destructors should only be managed by the engine?
        Scene();
        virtual ~Scene();
        
        virtual void Update(float);
        virtual void Render();

        unsigned int GetID() const { return id; }
        void AddGameObject(GameObject* newGameObject);

        void RegisterCamera(Camera* newCamera) { if (newCamera) cameras.push_back(newCamera); }
        //TO-DO: void RemoveCamera(Camera* newCamera) { if (newCamera) cameras.push_back(newCamera); }
        
        void UpdateCameras(int newWidth, int newHeight)
        {
            for (Camera* cam : cameras) if (cam) cam->AdaptToResize(newWidth, newHeight);
        }

    protected:
        unsigned int id;
        GameObject* root;
        std::vector<Camera*> cameras;

        void SetID(unsigned int newID) { id = newID; }
    };
}