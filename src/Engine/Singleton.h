#pragma once

template <class T>
class Singleton
{
    public:
        //Provide global access to the only instance of this class
        static T* Instance()
        {
            if (!instance)	//This if statement prevents the costly Lock-step being required each time the instance is requested
            {
                if (!instance) //Check to see if a previous thread has already initialised an instance in the time it took to acquire a lock.
                {
                    instance = new T();
                }
            }
            
            return instance;
        }

        //Provide global access to release/delete this class
        static void Release()
        {
            if (instance)
            {
                delete instance;
                instance = nullptr;
            }
        }

    protected:
        //Only allow the class to be created and destroyed by itself
        Singleton() {}
        ~Singleton() {}


    private:
        //Prevent the class from being copied either by '=' operator or by copy constructor
        Singleton(Singleton const&) {}
        Singleton& operator=(Singleton const&) {}

        //Keep a static instance pointer to refer to as required by the rest of the program
        static T* instance;
};

//Finally make sure that the instance is initialised to NULL at the start of the program
template <class T> T* Singleton<T>::instance = nullptr;