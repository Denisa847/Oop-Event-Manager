#pragma once
#include "Repository.h"
#include <vector>

//The administrator class handles operations on the repository
//such as adding,removing and updating
class Administrator
{
private:
	Repository& RepoEvents;

public:
	//Constructor
	Administrator(Repository& initialEvents);
	//Returns the dynamic vector of all current events
	std::vector<Event> getEvents();
	//Initializes the repository with a list with predefined events 
	//void initServices();
	//Generates random date and time
	//DateTime generateDateTime();
	//Adds an event with the provided detalies
	int addEvent(std::string title, std::string description, DateTime dateTime, int nrpeople, std::string link);
	//Removes an event identified by title and description
	int removeEvent(std::string title, std::string description);
	//Updates an existing event 
	int updateEvent(std::string title, std::string description, std::string Newtitle, std::string Newdescription, DateTime NewdateTime, int Newnrpeople, std::string Newlink);
};