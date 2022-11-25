// File:		Code.cpp
// Name:		Emir Khanseitov
// Date:		17.11.2022
// Description: This file contains the 'main' function. It is the entry point for the entire test.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declaration
class Object;
template <typename T>
class ObjectManager;
class Entity;
class EntityAction;
class EntityActionManager;


/*
Object class which is the base class for all the objects
*/
class Object
{
private:
    Entity *m_owner; // Owner of the object
    bool m_isActive; // Is the object active

public:
    Object(Entity *owner) : m_owner(owner), m_isActive(true) {}
    virtual ~Object() {}
};


/*
A templated class which is used to manage all the objects of a particular type
*/
template <typename T>
class ObjectManager
{
public:
    vector<T *> objects; // List of all the objects of type T
    ObjectManager() {}
    ~ObjectManager() {}

    // Add a new object of type T
    void Add(T *object)
    {
        objects.push_back(object);
    }

    // Remove an object of type T
    void Remove(T *object)
    {
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i] == object)
            {
                objects.erase(objects.begin() + i);
                break;
            }
        }
    }

    // display all the objects of type T in
    void ShowObjects()
    {
        if (objects.size() == 0)
        {
            cout << "No objects in this manager" << endl;
        }
        else
        {
            for (auto object : objects)
            {
                cout << typeid(*object).name() << endl;
            }
        }
    }
};


/*
This class inherits from Object class and is used to represent an entity's action in the game.
*/
class EntityAction : public Object
{
public:
    EntityAction(Entity *owner) : Object(owner) {}
    virtual ~EntityAction() {}
    virtual bool CanBeVisible() { return true; }
};


/*
EntityAction Manager is used to manage the actions of an entity. In the game, an entity can have multiple actions.
For example, a player can have actions like "Move", "Attack", "Pickup", "Drop" etc.
*/
class EntityActionManager : public ObjectManager<EntityAction>
{
public:
    EntityActionManager() {}
    ~EntityActionManager() {}

    vector<EntityAction *> GetVisibleActions()
    {
        vector<EntityAction *> visibleActions;
        for (auto action : objects)
        {
            if (action->CanBeVisible())
            {
                visibleActions.push_back(action);
            }
        }
        return visibleActions;
    }
};


// Entity class which is the base class for all the entities
class Entity
{
private:
    ObjectManager<Object> m_objectManager; // Object manager for all the objects of type Object
    EntityActionManager m_actionManager;   // Object manager for all the objects of type EntityAction

public:
    Entity() {}
    ~Entity() {}

    // add a new object of type T to the object manager
    template <typename T>
    T *AddComponent()
    {
        T *object = new T(this);
        m_objectManager.Add(object);
        m_actionManager.Add(object);
        return object;
    }

    // remove an object of type T from the object manager
    template <typename T>
    void RemoveComponent()
    {
        T *object = GetComponent<T>();
        m_objectManager.Remove(object);
        m_actionManager.Remove(object);
        delete object;
    }

    // get an object of type T from the object manager
    template <typename T>
    T *GetComponent()
    {
        for (auto object : m_objectManager.objects)
        {
            if (dynamic_cast<T *>(object))
            {
                return dynamic_cast<T *>(object);
            }
        }
        return nullptr;
    }

    // display all the objects of type T in the object manager
    void ShowComponents()
    {
        m_objectManager.ShowObjects();
    }

    // display all the objects of type EntityAction in the action manager
    void ShowActions()
    {
        m_actionManager.ShowObjects();
    }

    // display all the visible objects of type EntityAction in the action manager
    vector<EntityAction *> GetVisibleActions()
    {
        return m_actionManager.GetVisibleActions();
    }
};

int main()
{
    Entity *iron_man = new Entity();

    // create some objects, related to iron_man and set iron_man as their owner
    Object *im_suit = new Object(iron_man);
    Object *im_jarvis = new Object(iron_man);

    // create object manager
    ObjectManager<Object> *im_objectManager = new ObjectManager<Object>();

    // add objects to object manager
    im_objectManager->Add(im_suit);
    im_objectManager->Add(im_jarvis);

    cout << "\nIron man object manager objects:" << endl;
    im_objectManager->ShowObjects();

    // creating few actions
    EntityAction *fly = new EntityAction(iron_man);
    EntityAction *scan = new EntityAction(iron_man);

    // create entity action manager
    EntityActionManager *im_actionManager = new EntityActionManager();
    im_actionManager->Add(fly);
    im_actionManager->Add(scan);

    // get visible actions from action manager
    vector<EntityAction *> visibleActions = im_actionManager->GetVisibleActions();

    cout << "\nIron man visible actions:" << endl;
    // print the visible actions
    for (auto action : visibleActions)
    {
        cout << typeid(*action).name() << endl;
    }

    // remove fly action from action manager
    im_actionManager->Remove(fly);

    // get visible actions from action manager
    visibleActions = im_actionManager->GetVisibleActions();

    cout << "\nAfter removing a entity action:" << endl;
    // print the visible actions
    for (auto action : visibleActions)
    {
        cout << typeid(*action).name() << endl;
    }

    // remove im_suit from object manager
    im_objectManager->Remove(im_suit);

    return 0;
}

