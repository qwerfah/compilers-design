#include "State.h"
#include "Uuid.h"

State::State() : _stateUid(newUUID())
{ }

const std::string& State::getUid() const
{
	return _stateUid;
}
