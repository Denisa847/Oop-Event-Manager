#pragma once
#include <string>
#include <vector>
#include "Events.h"

class FilePersonalList {

public:
	virtual void save(const std::vector<Event>& events)const = 0;
	virtual std::string getFilename() const = 0;
	virtual ~FilePersonalList() = default;
};
