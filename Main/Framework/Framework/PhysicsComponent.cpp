#pragma once
#include "PhysicsComponent.h"
#include "GameObject.h"

float scalingFactor = 100.0f;

PhysicsComponent::PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_, b2World* _world, b2BodyType bodyType, float density) : Component(ComponentType::Physics, myObject_, mySystem_)
{
	direction = b2Vec2(0, 0);
	float y;
	float x;

	world = _world;

	//b2PolygonShape shape;

	//b2PolygonShape* ps = new b2PolygonShape();
	//ps->SetAsBox( 2, 2);
	//objShape = ps;
	objShape.SetAsBox(2, 2);
	bodyDef.type = bodyType;
	bodyDef.position.Set(myObject_->GetPosition().x, myObject_->GetPosition().y);
	body = world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &objShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);	// bind shape with body

	x = (body->GetPosition().x - 2) * scalingFactor;
	y = (body->GetPosition().y + 2) * scalingFactor * -1.0f;
	myObject_->SetGraphicsPosition(x, y);
	//myObject_->SetGraphicsSize(b2Vec2(2 * scalingFactor, 2 * scalingFactor));
}


PhysicsComponent::PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_, b2World* _world, b2BodyType bodyType, float density, float xWidth, float yWidth) : Component(ComponentType::Physics, myObject_, mySystem_)
{
	direction = b2Vec2(0, 0);
	float y;
	float x;

	world = _world;

	objShape.SetAsBox(xWidth /2, yWidth/2);
	bodyDef.type = bodyType;
	bodyDef.position.Set(myObject_->GetPosition().x, myObject_->GetPosition().y);
	body = world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &objShape;
	fixtureDef.density = density;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);	// bind shape with body

	x = (body->GetPosition().x - 2) * scalingFactor;
	y = (body->GetPosition().y + 2) * scalingFactor * -1.0f;
	myObject_->SetGraphicsPosition(x, y);
}


PhysicsComponent::~PhysicsComponent()
{
}

inline PhysicsComponent& PhysicsComponent::operator=(const PhysicsComponent& other)
{
	if (this == &other)
	{
		return *this;
	}

	memcpy(this, &other, sizeof(other));
	return *this;
}

b2Vec2 graphicsPos(0,0);

void PhysicsComponent::UpdateGraphicsPosition() 
{
	graphicsPos.x = (body->GetPosition().x - 2) * scalingFactor;
	graphicsPos.y = (body->GetPosition().y + 2) * scalingFactor * -1.0f;
	myObject->SetGraphicsPosition( graphicsPos.x, graphicsPos.y);
	//std::cout << " Gp X: " << myObject->GetGraphicsPosition().x << " Y: " << myObject->GetGraphicsPosition().x << " Pos X: " << myObject->GetPosition().x << " Y: " << myObject->GetPosition().x << std::endl;
}


void PhysicsComponent::SetVelocity(float xV, float yV)
{
	body->SetLinearVelocity(b2Vec2(xV, yV));
}

void PhysicsComponent::AddToDirection(b2Vec2 vec)
{
	direction += vec;
}

void PhysicsComponent::UpdateVelocity()
{
	direction.Normalize();
	direction *= speed;
	//printf("X: %6.3f , Y: %6.3f  \n", direction.x, direction.y);
}

void PhysicsComponent::SetDirectionToZero()
{
	direction.SetZero();
}


void PhysicsComponent::Update()
{
	UpdateVelocity();
	body->SetLinearVelocity(direction);
	myObject->SetPosition(body->GetPosition());
	UpdateGraphicsPosition();
	//printf("X: %3.3f , Y: %3.3f  \n", body->GetLinearVelocity().x, body->GetLinearVelocity().y);
	//printf("X: %3.3f , Y: %3.3f  \n", body->GetPosition().x, body->GetPosition().y);
}


