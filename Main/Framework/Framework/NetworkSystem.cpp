#include "NetworkSystem.h"
#include "GameObject.h"

void NetworkSystem::Update()
{
	for (int i = 0; i < gameObjects->size(); i++)
	{
		if (gameObjects->at(i)->GetNetworkID() == 0 && gameObjects->at(i)->idRequested == false)
		{
			RequestNetworkID(gameObjects->at(i));
			gameObjects->at(i)->idRequested = true;
		}
	}
	sf::IpAddress endPoint;
	std::size_t received;

	// receive packet
	socket.receive(data, sizeof(data), received, endPoint, port);

	// open and check what's inside
	FromPacket(data);

	//for (int i = 0; i < gameObjects->size(); i++)
	//{
	//	// ofr each game object
	//	//ToPacket();

	//	//SendUpdate();
	//}

	// bunch of if 's to check whats inside the message

}

std::string NetworkSystem::ToPacket(GameObject obj)
{
	return std::string();
}

void NetworkSystem::FromPacket(std::string recv)
{

	// bunch of if 's to check whats inside the message
	if (text.find("Object with id;") != std::string::npos)
	{
		 //find ip on list of connected clients and send it corresponding id
		std::stringstream split(data);
		std::string segment;
		std::vector<std::string> segmentlist;

		for (int i = 0; i < 4; i++)
		{
			std::getline(split, segment, ';');
			segmentlist.push_back(segment);
			std::cout << segmentlist.back() << std::endl;
		}

		for (int i = 0; i < gameObjects->size(); i++)
		{
			if (std::to_string(gameObjects->at(i)->GetObjectID()) == segmentlist.at(1))
			{
				gameObjects->at(i)->SetNetworkID(stoi(segmentlist.at(4)));
				std::cout << "Network ID of local obj: " + std::to_string(gameObjects->at(i)->GetObjectID()) + " has been assigned: " + std::to_string(gameObjects->at(i)->GetNetworkID()) << std::endl;
				break;
			}
		}
	}

}

void NetworkSystem::RequestNetworkID(GameObject* obj)
{
	//"Request id for local object:
	std::string request = "Request id for local object;" + std::to_string(obj->GetObjectID()) + ";";

	if (socket.send(request.c_str(), sizeof(request), serverIp, serverPort) != sf::Socket::Done)
	{
		std::cout << "UDP socket send() error" << std::endl;
	}
	std::cout << "Requesting Network ID" << std::endl;


}

void NetworkSystem::SendUpdate()
{
}

void NetworkSystem::UpdateGame()
{
}
