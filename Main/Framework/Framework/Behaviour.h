#pragma once
#include "Commons.h"
class Behaviour
{
	public:
		Behaviour(BehaviourType type_, std::string myString_) : type(type_), myString(myString_) {};
		Behaviour(const Behaviour& other) { type = other.type, myString = other.myString; }
		Behaviour& operator=(const Behaviour& other);

		inline BehaviourType getType() { return type; }
		inline std::string getString() { return myString; }

private:
	BehaviourType type;
	std::string myString;

};

