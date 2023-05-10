#pragma once
#include "Commons.h"
#include "Subsystem.h"
#include <SFML/Network.hpp>
#include <sstream>

class NetworkSystem : public Subsystem
{
	/*
	Network system should send updates on position, rotation etc of the local player, and receive updates about other objects and players
	*/
	// https://www.youtube.com/watch?v=kOXiLUTivHw&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg&index=24

public:
	NetworkSystem(EventQueue* _eventQueue, std::vector<GameObject*>* _gameObjects) : Subsystem(SubsystemType::Network, _eventQueue, _gameObjects)
	{
		// UDP socket set up
		socket.bind(port);
		socket.setBlocking(false);

		data = new char;

		gameObjects = _gameObjects;

	}

	void Update();
	Component* addComponent(Component* component_) { return 0; };
	int getNumComponents() { return 0; };

	// prepare packet containing all information about given game object
	std::string ToPacket(GameObject obj);
	void FromPacket(std::string recv);
	void RequestNetworkID(GameObject* obj);
	void SendUpdate();
	void UpdateGame();

private:
	//std::vector<NetworkComponent>* components;
	sf::IpAddress myIp = sf::IpAddress::getLocalAddress();
	std::vector<GameObject*>* gameObjects;
	sf::IpAddress serverIp = "192.168.0.228"; // must be set before using this system
	unsigned short serverPort = 2023; // must be set before using this system
	sf::UdpSocket socket;
	unsigned short port = 9050;
	char* data;
	std::string text;
};

