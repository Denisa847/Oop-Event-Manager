#pragma once
#include "Events.h"
#include "Exception.h"
#include "Repository.h"

class Validator {
public:
	static void validate(const Event& ev) {
		std::string errors;

		if (ev.getTitle().empty()) errors += "Title cannot be empty.\n";
		if (ev.getDescription().empty()) errors += "Description cannot be empty.\n";
		if (ev.getLink().empty()) errors += "Link cannot be empty.\n";


		if (ev.getNrPeople() < 0) errors += "Number of people must be non-negative.\n";

		if (ev.getDateTime().date < 1 || ev.getDateTime().date > 28) errors += "Invalid date.\n";
		if (ev.getDateTime().month < 1 || ev.getDateTime().month > 12) errors += "Invalid month.\n";
		if (ev.getDateTime().hour < 0 || ev.getDateTime().hour > 23) errors += "Invalid hour.\n";
		if (ev.getDateTime().minutes < 0 || ev.getDateTime().minutes > 59) errors += "Invalid minutes.\n";

		if (!errors.empty()) throw Exception(errors);
	}

	static void checkDuplicate(const Event& ev, const Repository& repo) {
		if (repo.getpos(ev) != -1)
			throw Exception("Event already exists!\n");
	}

	static void checkEventExists(int ind, const Repository& repo) {
		if (ind < 0 || ind >= static_cast<int>(repo.getEvents().size()))
			throw Exception("Event not found!\n");

	}

	static void validTitleandDescription(const std::string title, const std::string description)
	{
		std::string errors;
		if (title.empty())  errors += "Title cannot be empty.\n";
		if (description.empty()) errors += "Description cannot be empty.\n";

		if (!errors.empty()) throw Exception(errors);
	}
};