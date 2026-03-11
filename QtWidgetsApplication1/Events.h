#pragma once
#include <string>
#include <iostream>

//Struct to represent date and time information
typedef struct {
	int date, month;
	int hour, minutes;

}DateTime;

//Class representing an event 
class Event
{
private:
	std::string title;
	std::string description;
	DateTime dateTime;
	int nrpeople;
	std::string link;

public:

	friend std::ostream& operator<<(std::ostream& out, const Event& ev);
	friend std::istream& operator>>(std::istream& in, Event& ev);

	//Default constructor, creates an empty event with default values
	Event() : title(""), description(""), dateTime({ 0,0,0,0 }), nrpeople(0), link("") {}
	//Initalizes a constructor with specific data
	Event(std::string title, std::string description, DateTime dateTime, int nrpeople, std::string link);
	//Getter for the title of an event
	std::string getTitle() const;
	//Getter for a description of an event
	std::string getDescription() const;
	//Getter for date and time
	DateTime getDateTime() const;
	//Getter for the number of people
	int getNrPeople() const;
	//Getter for the link
	std::string getLink() const;
	//Equality operator:compares to events based on title and description
	bool operator==(const Event& ev)const;
	//Assignment operator: assignes one event to another
	void operator=(const Event& ev);
	void setNrPeople(int people);




};