#pragma once
#include "Commons.h"
//#include "Component.h"
class Component;

class GameObject
{
public:
	static int objectCount;

	GameObject();
	GameObject(std::string name_);
	GameObject(std::string name_, b2Vec2 position_);
	GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_);
	GameObject(std::string name_, std::unordered_map<ComponentType, Component*> components_, b2Vec2 position_);

	GameObject(const GameObject& other);

	~GameObject();

	GameObject& operator=(const GameObject& other);

	void addComponent(Component* component_);
	Component* getComponent(ComponentType type_);
	inline std::string getName() { return *name; };
	inline void setName(std::string name_) { *name = name_; }
	inline void SetPosition(float x, float y) {	position.Set(x, y);	}
	inline void SetPosition(b2Vec2 pos_) { position = pos_; }

	inline b2Vec2 GetPosition() { return position; };
	inline b2Vec2 GetGraphicsPosition() { return graphicsPosition; };
	inline void SetGraphicsPosition(float x, float y) { graphicsPosition.Set(x, y); }

	// return scaled size of the object so that it can be used by graphics component
	b2Vec2 GetSizeFromPhysics() {	return graphicsSize;	}
	void SetGraphicsSize(b2Vec2 a) { graphicsSize = a; }

	unsigned int GetObjectID() { return objectID; }
	unsigned int GetNetworkID() { return networkID; }
	void SetNetworkID(int id_) { networkID = id_; }

	bool networkUpdates = true;
	bool idRequested = false;

private:
	// objectID works as local id for objects, it will be used in networking
	unsigned int objectID;
	unsigned int networkID = 0;

	std::string* name;
	std::unordered_map<ComponentType, Component*> components;
	b2Vec2 position;	
	// position in physics world, it will be "translated" into pixels in graphics component
	// would it be easier to give GameObject a Box2D body?
	// isn't position already stored by box2D in boydef or smth?
	b2Vec2 graphicsPosition = b2Vec2_zero;
	
	// Size of thge displayed shape is dependant on physical size set by physics component
	// this way user don't need to worry about correctly scaling both components to match each other
	b2Vec2 graphicsSize = b2Vec2_zero;


};

