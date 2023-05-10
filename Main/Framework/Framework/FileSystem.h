#pragma once
#include "Commons.h"
#include "Subsystem.h"
#include <jsoncpp/json/json.h>
#include <fstream>

class FileSystem : public Subsystem
{
public:
    // singleton pattern to make sure that there is only one FileSystem instance 
    static FileSystem& instance(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects)
    {
        static FileSystem* instance = new FileSystem(_eventQueue, _gameObjects);
        return *instance;
    }

    // Files system will not have any components
    // all events will be processed by the system itself


    void ReadFile(std::string file);
    void SaveLevel();

    // in update system will look for filesystem events
    void Update();
    Component* addComponent(Component* component_) { return nullptr; };
    int getNumComponents() { return 0; };
    Json::Value fileData;


private:
    FileSystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects) : Subsystem(SubsystemType::FileSystem, _eventQueue, _gameObjects) 
    {
    }
    
};

