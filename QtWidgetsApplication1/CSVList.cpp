#include "CSVList.h"
#include <fstream>
#include "Exception.h"

CSVList::CSVList(const std::string& fname) : filename(fname) {}

void CSVList::save(const std::vector<Event>& events) const {
	std::ofstream fout(filename);
	//std::ofstream fout(filename, std::ios::app);
	if (!fout.is_open())
		throw Exception("Could not open the file for writing!");

	for (const auto& ev : events) {
		fout << ev.getTitle() << ","
			<< ev.getDescription() << ","
			<< ev.getDateTime().date << "."
			<< ev.getDateTime().month << ".2025,"
			<< ev.getDateTime().hour << ":"
			<< ev.getDateTime().minutes << ","
			<< ev.getNrPeople() << ","
			<< ev.getLink() << "\n";
	}
	fout.close();

}

std::string CSVList::getFilename() const {
	return filename;
}