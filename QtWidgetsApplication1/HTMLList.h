#pragma once
#include <vector>
#include "FilePersonalList.h"
#include <fstream>
#include "Events.h"

class HTMLList : public FilePersonalList {
private:
	std::string filename;

public:
	HTMLList(const std::string& fname);
	void save(const std::vector<Event>& events) const override;
	std::string getFilename() const override;
};