#pragma once
#include "Events.h"
#include <vector>

//Repository class manages a collection of Event objescts using a stl vector
class Repository
{
private:
	std::vector<Event> Events;

public:
	//Constructor 
	Repository(const std::vector<Event>& startEvents = {});
	//Returns a copy of all events stored in the repository
	std::vector<Event> getEvents() const;
	//Adds a new event to the repository if it doesn't already exists
	int addEvent(const Event& newEvent);
	//Removes an event from a specific index if it exists
	int removeEvent(int ind);
	//updates an event from a specific index if it exists
	int updateEvent(int ind, const Event& updatedEvent);
	//returns the index of an event  or -1 if it does not find it
	int getpos(const Event& eventpos)const;

	void loadFromFile(const std::string& filename);
	void saveToFile(const std::string& filename) const;

};