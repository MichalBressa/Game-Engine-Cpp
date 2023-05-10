// 6020_server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Network.hpp>
#include <string>
#include <vector>
#include <map>
#include <sstream>
int main()
{

    // at the moment I want to do a proper handshake between server and client 
    // to make reliable handshake will use TCP protocol
    // when game will start running UDP should be used for best performance (it is faster than TCP becuase it performs less checks)

    static unsigned int lastAssignedID = 0;

    // each connected client will request unique id for its locally owned objects
    // when received update about certain object server will sotre it and then send to other clients

    // map of assigned id , ip address of the clients
    std::vector<sf::IpAddress> clientsList;

    // id of client and last data from him
    std::map<int, std::string> gameState;

    sf::IpAddress serverIp = sf::IpAddress::getLocalAddress();

    bool IPisInMap;

    char data[2048];
    data[0] = 0;
    std::string text;
    std::size_t received;
    unsigned short port = 9050;

    // UDP socket:
    // bind = socket is listeing to the port
    sf::UdpSocket udpSocket;
    udpSocket.bind(2023);

    // blocking stops thread containing function call to receive until it finished 
    // the thread would wait till receives any data, which may result in blocking entire program
    udpSocket.setBlocking(false);

    // ---------- loop ----------//

    while (true) 
    {
        sf::IpAddress endPoint;
        
        // listen for packets
        if (udpSocket.receive(data, sizeof(data), received, endPoint, port) != sf::Socket::Done)
        {
            //std::cout << "UDP socket receive() error" << std::endl;
        }
    /*  if (data[0] != 0) 
        {
            std::cout << "Received " << received << " bytes from " << endPoint << " on port " << port << std::endl;
        }*/
  

        IPisInMap = false;

        // check if IP is on the list
        for (int i = 0; i < clientsList.size(); i++) 
        {
            //std::find(clientsList.begin(), clientsList.end(), endPoint) != clientsList.end()
            if (std::find(clientsList.begin(), clientsList.end(), endPoint) != clientsList.end())
            {
                IPisInMap = true;
            }
            
            if(!IPisInMap)
            {
                // add ip to the map
                clientsList.push_back(endPoint);
                std::cout << "New client connected from " << endPoint << std::endl;
            }
        }
        text = data;
        // check received message for certain keywords and respond based on that
        if (text.find("Request id for local object;") != std::string::npos) 
        {
            // find ip on list of connected clients and send it corresponding id
            //int index = text.find("Request id for local object:") + 1;

            std::stringstream split(data);
            std::string segment;
            std::vector<std::string> segmentlist;

            for (int i = 0; i < 2; i++)
            {
                std::getline(split, segment, ';');
                segmentlist.push_back(segment);
                std::cout << segmentlist.back() << std::endl;
            }

            std::string returnMsg = "Object with id;" + segmentlist.at(1) + "; network ID is;" + std::to_string(lastAssignedID) + ";";
            std::cout << returnMsg << std::endl;
            lastAssignedID++;
            if(udpSocket.send(returnMsg.c_str(), sizeof(returnMsg), endPoint, port) != sf::Socket::Done)
            {
                //std::cout << "UDP socket send() error" << std::endl;
            }
        }
        else if (text.find("Object data;") != std::string::npos) 
        {

            std::stringstream split(data);
            std::string segment;
            std::vector<std::string> segmentlist;

            for (int i = 0; i < 2; i++)
            {
                std::getline(split, segment, ';');
                segmentlist.push_back(segment);
                std::cout << segmentlist.back() << std::endl;
            } 
            
            int objId = std::stoi(segmentlist.at(1));

            if (gameState.find(objId) != gameState.end()) 
            {
                // if we are already tracking this object we simply save last update about it
                auto it = gameState.find(objId);
                it->second = text;
            }
            else 
            {
                //if not then we add it to the objects and its data
                gameState.insert(std::pair<int, std::string>(objId, text));
            }

        }

        // each client shall receive update about all objects
        for (int i = 0; i < clientsList.size(); i++) 
        {
            for (int j = 0; j < gameState.size(); j++)
            {
                // send data
                if (udpSocket.send(gameState[j].c_str(), sizeof(gameState[j]), clientsList.at(i), port) != sf::Socket::Done)
                {
                    std::cout << "Error while sending data to clients" << std::endl;
                }
            }
        }
        // reset value to avoid errors
        text = "";


    }

}
