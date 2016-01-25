#pragma once

#include "GameObject.h"

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

    protected:
        unsigned int id;
        GameObject* root;

        void SetID(unsigned int newID) { id = newID; }
    };
}