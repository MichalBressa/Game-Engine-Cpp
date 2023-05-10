#pragma once
#include "Commons.h"
#include "Component.h"

class PhysicsComponent : public Component
{
	/*
	Creating Box2D object
	1. Create body definition
	2. Create the body
	3. Create shape
	4. Bind all together 	
	*/

	public:
		PhysicsComponent(GameObject * myObject_, Subsystem * mySystem_, b2World* _world, b2BodyType bodyType, float density);

		// constructor for ractangles only
		PhysicsComponent(GameObject* myObject_, Subsystem* mySystem_, b2World* _world, b2BodyType bodyType, float density, float xWidth, float yWidth);


		//PhysicsComponent(const PhysicsComponent & other) : Component(ComponentType::Physics, other.myObject, other.mySystem)
		//{
		//	//bodyDef = other.bodyDef;
		//	body = other.body;
		//	world = other.world;
		//	objShape = other.objShape;
		//	direction = b2Vec2(0, 0);
		//};

		~PhysicsComponent();

		PhysicsComponent& operator=(const PhysicsComponent & other);
		void SetVelocity(float xV, float yV);
		void AddToDirection(b2Vec2 vec);
		void Update();
		void UpdateVelocity();
		void UpdateGraphicsPosition();
		void SetDirectionToZero();
		void SetMaxSpeed(float v) { speed = v; }

	private:
		/* This is where you stick data unique to the physics component! */
		b2BodyDef bodyDef;
		b2Body* body;
		b2World* world;
		b2Vec2 position;
		float speed = 0.1f;
		b2Vec2 direction;
		b2PolygonShape objShape;
};

