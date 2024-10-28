#include "static.h"

tlx::Error::~Error(void)
{
	if (this->message)
		delete this->message;
}
