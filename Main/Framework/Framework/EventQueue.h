#pragma once
#include "Event.h"
#include "Commons.h"


class EventQueue
{
public:
	EventQueue() { InitialiseFunctionMaps(); }
	~EventQueue();
	std::vector<Event*> events;
	void popEvent(Event* event_);

	std::unordered_map<SubsystemType, std::unordered_map<EventType, void(*)(Event*)>*> functionMap;

	void InitialiseFunctionMaps();
	std::vector< std::unordered_map<EventType, void(*)(Event*)>*> functionMaps;

};

