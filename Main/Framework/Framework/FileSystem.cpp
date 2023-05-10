#include "FileSystem.h"
#include "EventQueue.h"

void FileSystem::ReadFile(std::string file)
{
	std::ifstream inFileStream(file);

	inFileStream >> fileData;
	inFileStream.close();
}

void FileSystem::SaveLevel()
{

}

void FileSystem::Update() 
{
	// in update it would be looking for save event that would mean that it is time to save all objects into json file


	//int eQsize = eventQueue->events.size();

	//if (eQsize > 0)
	//{
	//	Event* temp;

	//	for (int i = 0; i < eQsize; i++)
	//	{
	//		/* If there's an event, we check it out, and see if it's
	//		 * something this subsystem cares about (== type).
	//		 */

	//		temp = eventQueue->events[i];

	//		for (int j = 0; j < temp->systems.size(); j++)
	//		{
	//			if (temp->systems[j] == type)
	//			{
	//				/* If we care about it, we know we'll have a function
	//				 * to deal with it somewhere in the eventQueue. We'll
	//				 * look into that in more detail in EventQueue.h
	//				 */

	//				auto it = eventQueue->functionMap.find(type);

	//				auto it2 = it->second->find(temp->type);

	//				/* We find our function and pass in the event as its
	//				 * parameter. We then pop our subsystem off the event's
	//				 * subsystem list, so we don't react to it twice!
	//				 */

	//				it2->second(temp);

	//				temp->systems.erase(temp->systems.begin() + j);

	//				/* If we were the last subsystem to react to the event,
	//				 * we remove it from the event queue entirely, to save
	//				 * memory. Let's have a look at the event queue in
	//				 * EventQueue.h
	//				 */

	//				if (temp->systems.size() == 0)
	//				{
	//					delete eventQueue->events[i];
	//					eventQueue->events.erase(eventQueue->events.begin() + i);
	//				}
	//			}
	//		}
	//	}
	//}
}
