#include "./Preprocessor.h"
#include "../../all.h"

tlx::frontend::Preprocessor::Preprocessor(const std::string& filename) : reading(filename)
{
	this->incs.push_back(filename);
}
tlx::frontend::Preprocessor::~Preprocessor(void)
{
	this->defines.clear();
	this->errs.clear()	 ;
	this->incs.clear()	 ;
}

std::string tlx::frontend::Preprocessor::process(void)
{
	std::string& filename_out = this->incs.at(0);
	struct tlx::Error err { tlx::Errors::PREPROCESSOR, 0, NULL};
	char*  msg;
	if (!reading.is_open()) {
		msg = strdup(std::string("File \"" + filename_out + "\" not found or cannot be opened").c_str());
		err.code = 1;
		this->errs.push_back(err);
		return "";
	}
	std::string filename_in = filename_out  + ".pre";
	std::ofstream file{ filename_in, std::ios::binary };
	if (!file.is_open()) {
		msg = strdup(std::string("New file \"" + filename_in + "\" is not opened").c_str());
		err.code = 2;
		err.message = msg;
		this->errs.push_back(err);
		return "";
	}
	std::string buffer = "";
	while (!reading.eof()) {
		readLine(buffer, reading);

	}
	reading.close();
}
