#include "GameObject.h"

//TO-DO: <algorithm> is required for the correct use of std::remove used in RemoveChild;
//       find a way to avoid using this.
//#include <algorithm>

namespace Symphony
{
    GameObject::GameObject()
    {
        parent = nullptr;
        name = "New GameObject";
    }

    GameObject::GameObject(Transform & t)
        : GameObject()
    {
        transform = t;
    }

    GameObject::~GameObject()
    {
    }

    /*void GameObject::RemoveChild(GameObject* c)
    {
        children.erase(std::remove(children.begin(), children.end(), c), children.end());
    }*/
}

