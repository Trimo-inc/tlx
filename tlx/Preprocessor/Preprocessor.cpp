#include "./Preprocessor.h"
#include "../../all.h"

tlx::frontend::Preprocessor::Preprocessor(const std::string& filename) : file_wr(filename + ".pre")
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
	std::string line = "";
	std::ifstream reading{ filename_out, std::ios::binary };
	if (!reading.is_open()) {
		this->writeError(tlx::frontend::OPEN_OUT);
		return line;
	}
	
	if (!this->file_wr.is_open()) {
		this->writeError(tlx::frontend::OPEN_IN);
		return line;
	}
	while (!reading.eof()) {
		readLine(line, reading);
		this->recursionIncludes(line, reading);
	}
	reading.close();
	this->file_wr.close();
}

void tlx::frontend::Preprocessor::process(const std::string& filename)
{
	std::ifstream file_read{ filename, std::ios::binary };
	if (!file_read.is_open()) {
		this->writeError(tlx::frontend::PreErrors::NOT_OPEN_FILE,
			"File \"" + filename + "\" is not opened");
		return;
	}
	std::string buffer = "";
	while (!file_read.eof()) {
		readLine(buffer, file_read);
		this->recursionIncludes(buffer, file_read);
	}

}

void tlx::frontend::Preprocessor::recursionIncludes(const std::string& buffer, std::ifstream& file_rd)
{
	std::size_t posi = 0, point = 0; // {$ $};
	const char dollar = '$';
	while (posi < buffer.size()) {
		if (point) { // find constructions

		}
		else {
			std::size_t posi2 = posi + 2;
			if (buffer[posi] == '{' && buffer[posi + 1] == dollar &&
			   (posi2 <= buffer.size() && buffer[posi2] != dollar)) {
				point++;
			}
		}
		this->file_wr << buffer[posi];
		posi++;
		
	}
}

void tlx::frontend::Preprocessor::writeError(const tlx::frontend::PreErrors& n)
{
	struct tlx::Error err { tlx::Errors::PREPROCESSOR, n };
	std::string msg;
	
	switch (n)
	{
		case tlx::frontend::OPEN_OUT: {
			std::string& filename_out = this->incs.at(0);
			msg = "File \"" + filename_out + "\" not found or cannot be opened";
			break;
		}
		case tlx::frontend::OPEN_IN: {
			msg = "New file for doing not created";
			break;
		}
	}
	err.message = strdup(msg.c_str());
	this->errs.push_back(err);
}
void tlx::frontend::Preprocessor::writeError(const tlx::frontend::PreErrors& code, const std::string& data)
{
	struct tlx::Error err{ tlx::Errors::PREPROCESSOR, code, strdup(data.c_str()) };
	this->errs.push_back(err);
}

