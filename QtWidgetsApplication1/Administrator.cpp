#include "Administrator.h"
#include <iostream>
#include <vector>
#include "Validator.h"
#include "Exception.h"

//Constructor that intializes the Administrator Services with an existing Repository of evenets 
Administrator::Administrator(Repository& initialEvents) :RepoEvents{ initialEvents }
{
	//nothing to do here
}


//Retrives the current list of all events from repository
std::vector<Event> Administrator::getEvents()
{
	return this->RepoEvents.getEvents();
}

//Adds an event to the repository and returns 1 if the event was added, 0 if already exists
int Administrator::addEvent(std::string title, std::string description, DateTime dateTime, int nrpeople, std::string link)
{
	Event newEvent{ title,description,dateTime, nrpeople, link };

	//validate
	Validator::validate(newEvent);
	Validator::checkDuplicate(newEvent, this->RepoEvents);

	return this->RepoEvents.addEvent(newEvent);
}


//Removes an event by matching its title and description and returns 1 if the event was removed,0 if the event was not found
int Administrator::removeEvent(std::string title, std::string description)
{//Constructs a temporary event using only title and description to compare
	DateTime changedateTime;
	changedateTime.date = 0;
	changedateTime.month = 0;
	changedateTime.hour = 0;
	changedateTime.minutes = 0;
	Event toRemove{ title,description,changedateTime,0,"" };
	//validator
	Validator::validTitleandDescription(title, description);
	int index = this->RepoEvents.getpos(toRemove);
	Validator::checkEventExists(index, this->RepoEvents);

	return this->RepoEvents.removeEvent(index);

}

//Updates an existing event and if the update was a succes returns 1, 0 if the original event was not found
int Administrator::updateEvent(std::string title, std::string description, std::string Newtitle, std::string Newdescription, DateTime NewdateTime, int Newnrpeople, std::string Newlink)
{
	DateTime changedateTime;
	changedateTime.date = 0;
	changedateTime.month = 0;
	changedateTime.hour = 0;
	changedateTime.minutes = 0;
	Event old{ title,description,changedateTime,0,"" };
	Event newEv{ Newtitle,Newdescription,NewdateTime,Newnrpeople,Newlink };

	//validate
	Validator::validate(newEv);
	int ind = this->RepoEvents.getpos(old);
	Validator::checkEventExists(ind, this->RepoEvents);

	return this->RepoEvents.updateEvent(ind, newEv);


}

/*
//Generate a random date and time for the events
DateTime Administrator::generateDateTime()
{
	DateTime dateTime;
	dateTime.date = rand() % 28 + 1;
	dateTime.month = rand() % 12 + 1;
	dateTime.hour = rand() % 24;
	dateTime.minutes = rand() % 60;

	return dateTime;


}


//Intializes the service with a list of 10 events
void Administrator::initServices()
{
	DateTime dateTime;

	this->addEvent("Music Festival", "Outdoor concert event", generateDateTime(), 1500, "https://shorturl.at/558uh");
	this->addEvent("Film Screening", "Outdoor film", generateDateTime(), 600, "https://shorturl.at/1VsOl");
	this->addEvent("Tech Conference", "Presentation of latest in tech", generateDateTime(), 400, "https://shorturl.at/h2kcC");
	this->addEvent("Marathon", "Annual city marathon", generateDateTime(), 200, "https://shorturl.at/3Z1EG");
	this->addEvent("Art Exhibit", "Modern art gallery", generateDateTime(), 140, "https://shorturl.at/ZcIpY");
	this->addEvent("Gaming Tournament", "Esports competion", generateDateTime(), 100, "https://kafugames.com/en");
	this->addEvent("Astronomy Night", "Stargazing with telescopes", generateDateTime(), 50, "https://shorturl.at/EcCYa");
	this->addEvent("Vintage Car Show", "Exhibition of classinc cars", generateDateTime(), 1000, "https://shorturl.at/YP7sG");
	this->addEvent("Yoga Retreat", "Mindfulness and Meditation weekend", generateDateTime(), 85, "https://shorturl.at/kWEnd");
	this->addEvent("Rock Music Festival", "Outdoor  rock concert event", generateDateTime(), 150, "https://shorturl.at/ennN1");


}

*/
