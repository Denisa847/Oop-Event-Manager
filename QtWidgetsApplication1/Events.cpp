#include "Events.h"
#include <sstream>

//Constructor to initialize and Event with all required attributes
Event::Event(std::string title, std::string description, DateTime dateTime, int nrpeople, std::string link)
{
	this->title = title;
	this->description = description;
	this->dateTime = dateTime;
	this->nrpeople = nrpeople;
	this->link = link;

}

//Getter for the title of the event
std::string Event::getTitle() const
{
	return this->title;
}

//Getter for the description of the event
std::string Event::getDescription() const
{
	return this->description;
}

//Getter for the data and time of the event
DateTime Event::getDateTime() const
{
	return this->dateTime;
}

//Getter for the number of people 
int Event::getNrPeople() const
{
	return this->nrpeople;
}

//Getter for the link of the event
std::string Event::getLink() const
{
	return this->link;
}

//Compares two events by their title and description and returns true if they match or 0 otherwise
bool Event::operator==(const Event& ev) const
{
	if (this->title == ev.title && this->description == ev.description)
		return true;
	return false;
}


//Assignes all attributes from another event to this one
void Event::operator=(const Event& ev)
{
	this->title = ev.title;
	this->description = ev.description;
	this->dateTime = ev.dateTime;
	this->nrpeople = ev.nrpeople;
	this->link = ev.link;
}

std::ostream& operator<<(std::ostream& out, const Event& ev)
{
	out << ev.title << "," << ev.description << "," << ev.dateTime.date << "."
		<< ev.dateTime.month << "," << ev.dateTime.hour << ":" << ev.dateTime.minutes << "," << ev.nrpeople << "," << ev.link << "\n";
	return out;
}

std::istream& operator>>(std::istream& in, Event& ev)
{/*
	std::string title, description, link;
	int date, month, hour, minutes, nrpeople;

	std::getline(in, title, ',');
	std::getline(in, description, ',');
	in >> date >> month >> hour >> minutes;
	in.ignore();
	in >> nrpeople;
	in.ignore();
	std::getline(in, link);


	ev = Event(title, description, DateTime{ date,month,hour,minutes }, nrpeople, link);
	return in;*/

	std::string line;
	if (!std::getline(in, line)) return in;

	std::istringstream ss(line);
	std::string title, description, dateStr, timeStr, nrpeopleStr, link;

	std::getline(ss, title, ',');
	std::getline(ss, description, ',');
	std::getline(ss, dateStr, ',');
	std::getline(ss, timeStr, ',');
	std::getline(ss, nrpeopleStr, ',');
	std::getline(ss, link);

	int day = 0, month = 0, hour = 0, minute = 0, nrpeople = 0;
	char dot, colon;

	std::istringstream(dateStr) >> day >> dot >> month;
	std::istringstream(timeStr) >> hour >> colon >> minute;
	nrpeople = std::stoi(nrpeopleStr);

	ev = Event(title, description, DateTime{ day, month, hour, minute }, nrpeople, link);
	return in;
}

void Event::setNrPeople(int people) {
	this->nrpeople = people;
}
