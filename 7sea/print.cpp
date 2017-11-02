#include "main.h"

logs::state logc;

logs::state::state()
{
	memcpy(this, &logc, sizeof(*this));
}

logs::state::~state()
{
	memcpy(&logc, this, sizeof(*this));
}

const char* logs::getpanel(int index)
{
	return logc.information;
}