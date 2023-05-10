#pragma once

#include "Behaviour.h"

Behaviour& Behaviour::operator=(const Behaviour& other)
{
	if (this == &other)
		return *this;

	Behaviour a(other.type, other.myString);
	return a;
}