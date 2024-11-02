#include "static.h"

extern std::string fullpath_dir;

tlx::Error::~Error(void)
{
	if (this->message)
		delete this->message;
}
void tlx::setPath(const char* fullpath)
{
	tlx::fullpath_dir = std::string(fullpath);
}