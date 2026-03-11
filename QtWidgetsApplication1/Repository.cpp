#include "Repository.h"
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include "Exception.h"
#include "Validator.h"

//Constructor that intializes the repository with an Vector of Events
Repository::Repository(const std::vector<Event>& startEvents) : Events{ startEvents }
{
	//nothing to do here
}

//Returns the current list of events
std::vector<Event> Repository::getEvents() const
{
	return this->Events;
}


//Adds an event to the repository and returns 1 if it was successfully added and 0 if the evenet already exists
int Repository::addEvent(const Event& newEvent)
{
	//if (getpos(newEvent) != -1)
		//return 0;
		//throw Exception("Event already exists!");

	this->Events.push_back(newEvent);
	return 1;
}


//Returns 1 if an eventwas successfully removed from a speciefied index, 0  otherwise 
int Repository::removeEvent(int ind)
{
	//if (ind < 0 || ind >= static_cast<int>(this->Events.size()))
		//return 0;

	this->Events.erase(this->Events.begin() + ind);
	return 1;
}


//Returns 1 if an event was successfully updated from a specified index,0 otherwise
int Repository::updateEvent(int ind, const Event& updatedEvent)
{
	//if (ind < 0 || ind >= static_cast<int>(this->Events.size()))
		//return 0;

	this->Events[ind] = updatedEvent;
	return 1;
}


//Returns the position of an event in the repository or -1 if it was not found
int Repository::getpos(const Event& eventpos) const
{
	auto it = std::find(this->Events.begin(), this->Events.end(), eventpos);
	if (it != this->Events.end())
		return static_cast<int>(std::distance(this->Events.begin(), it));
	return -1;
}


void Repository::loadFromFile(const std::string& filename)
{
	std::ifstream fin(filename);
	//validator
	if (!fin.is_open())
		throw Exception("Could not open the file for reading!");

	this->Events.clear();

	std::string line;
	while (std::getline(fin, line)) {
		// --- trim spaces ---
		line.erase(0, line.find_first_not_of(" \t"));
		line.erase(line.find_last_not_of(" \t") + 1);

		if (line.empty())
			continue; // Skip empty/space-only lines

		std::istringstream ss(line);

		Event ev;
		ss >> ev;

		try {
			Validator::validate(ev);
			this->Events.push_back(ev);
		}
		catch (const Exception& e) {
			std::cerr << "Error loading event: " << e.what() << "\n";
			continue;
		}
	}

	/*
	Event ev;
	while (fin >> ev) {
		try {
			Validator::validate(ev);
			this->Events.push_back(ev);
		}
		catch (const Exception& e) {
			std::cerr << "Error loading event: " << e.what() << "\n";
			continue;
		}
	}*/

	fin.close();
}

void Repository::saveToFile(const std::string& filename) const {
	std::ofstream fout(filename);
	//validator
	if (!fout.is_open())
		throw Exception("Could not open the file for writing!");

	for (const auto& ev : Events) {
		fout << ev;
	}

	fout.close();

}