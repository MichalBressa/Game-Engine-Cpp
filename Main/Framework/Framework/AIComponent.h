#pragma once
#include "Commons.h"
#include "Component.h"
#include "Behaviour.h"

class AIComponent : public Component
{
public:
	AIComponent(GameObject* myObject_, Subsystem* mySystem_) : Component(ComponentType::AI, myObject_, mySystem_)
	{
		currentBehaviour = nullptr; behaviours = new std::vector<Behaviour*>; inRange = false;
	};

	AIComponent(const AIComponent& other);

	AIComponent& operator=(const AIComponent& other);

	inline std::vector<Behaviour*>* getBehaviours() { return behaviours; }
	inline Behaviour* getCurrentBehaviour() { return currentBehaviour; }
	inline void setCurrentBehaviour(Behaviour* behaviour_) { currentBehaviour = behaviour_; }

	void addBehaviour(BehaviourType type_, std::string myString_);
	inline void removeBehaviour(int i_) { behaviours->erase(behaviours->begin() + i_); }

	inline int getBehaviourCount() { if (behaviours != nullptr) return behaviours->size(); return -1; }

	void setPatrol();

	void Update();

	inline void setInRange(bool inRange_) { inRange = inRange_; }

private:
	std::vector<Behaviour*>* behaviours;
	std::unordered_map<BehaviourType, Behaviour*> behaviourMap;
	Behaviour* currentBehaviour;
	bool inRange;
};
