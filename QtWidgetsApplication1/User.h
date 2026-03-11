#pragma once
#include "Repository.h"
#include <vector>
#include <string>
#include "FilePersonalList.h"

class User {
private:
	Repository& repo;
	std::vector<Event> list;
	FilePersonalList* fileList;


public:
	//Constructor of the user class
	User(Repository& initial, FilePersonalList* fileList);
	//this function returns events filtered by month or all the events if the month was not given
	std::vector<Event> getEventsbyMonth(const std::vector<Event>& events, int month);
	//Adds an event to the user's personal list from the list of events
	bool addEvent(const Event& ev);
	//It delets an event from the user's list by matching its title and description
	bool deleteEvent(std::string title, std::string description);
	//Returns the user's list of events
	std::vector<Event> getlist() const;
	//Returns a list of events filtered by month
	std::vector<Event> getEventsofMonth(const std::vector<Event>& allEvents, int month);

	void saveList() const;
	FilePersonalList* getFileList() const;
};