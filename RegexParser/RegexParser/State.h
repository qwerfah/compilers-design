#pragma once

#include <string>

class State
{
public:
	State();

	const std::string& getUid() const;

private:
	const std::string _stateUid;
};

