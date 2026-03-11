#pragma once
#include <string>
#include <vector>
#include "FilePersonalList.h"
#include <fstream>

class CSVList : public FilePersonalList {
	std::string filename;
public:
	CSVList(const std::string& fname);
	void save(const std::vector<Event>& events) const override;
	std::string getFilename() const override;

};