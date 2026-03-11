#include "HTMLList.h"
#include <fstream>
#include "Exception.h"
#include <vector>

HTMLList::HTMLList(const std::string& fname) : filename(fname) {}

void HTMLList::save(const std::vector<Event>& events) const {
	std::ofstream fout(filename);
	if (!fout.is_open())
		throw Exception("Could not open the HTML file for writing");
	fout << "<!DOCTYPE html>\n<html>\n<head>\n<title>My Events</title>\n</head>\n<body>\n";
	fout << "<table border='1'>\n";
	fout << "<tr><th>Title</th><th>Description</th><th>Date</th><th>Time</th><th>Number of People</th><th>Link</th></tr>\n";

	for (const auto& ev : events) {
		fout << "<tr>";
		fout << "<td>" << ev.getTitle() << "</td>";
		fout << "<td>" << ev.getDescription() << "</td>";
		fout << "<td>" << ev.getDateTime().date << "." << ev.getDateTime().month << ".2025" << "</td>";
		fout << "<td>" << ev.getDateTime().hour << ":" << ev.getDateTime().minutes << "</td>";
		fout << "<td>" << ev.getNrPeople() << "</td>";
		fout << "<td><a href='" << ev.getLink() << "'>Link</a></td>";
		fout << "</tr>\n";
	}
	fout << "</table>\n</body>\n</html>";
	fout.close();
}

std::string HTMLList::getFilename() const {
	return filename;
}