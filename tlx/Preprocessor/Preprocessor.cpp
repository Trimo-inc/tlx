#include "./Preprocessor.h"
#include "../../all.h"

#include <filesystem>
#include <regex>

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
	const char include = "include";
	static const unsigned short limit_reading = 4096;
	while (posi < buffer.size()) {
		if (point) { // find constructions
			if (buffer[posi] == dollar && buffer[posi + 1] == '}') {
				point--;
			}
			else {
				std::size_t find = buffer.find(include);
				if (find != std::string::npos) {
					posi += find + 8; // 8 is lenght word 'include'
					while ((posi <= buffer.size() && posi < limit_reading) && (isspace(buffer[posi]))) {
						posi++;
					}
					char dk; // if (") else (')
					if (posi < buffer.size() && (buffer[posi] == '\"' || buffer[posi] == '\'')) {
						dk = buffer[posi];
						std::string filename = "";
						while (posi <= buffer.size() && (buffer[posi] != dk) | ) {
							filename += buffer[posi++];
						}
						if (buffer[posi] != dk) {
							this->writeError(tlx::frontend::PreErrors::SYNTAX, "Expected " + dk + " symbol");
							return;
						} posi++;
						if (this->isNotFoundFilename(filename)) {
							findFiles(filename); // Recursion fucntion
						} 

					}
					else {
						this->writeError(tlx::frontend::PreErrors::SYNTAX);
					}
				}
			}
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
	this->file_wr << buffer[posi];
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
		case tlx::frontend::SYNTAX: {
			msg = "Expected \" or \' symbols";
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

bool tlx::frontend::Preprocessor::isNotFoundFilename(const std::string& name)
{
	const char* p_n = name.c_str();
	std::size_t size = name.size();
	for (const auto& iter : this->incs) {
		if (!strncmp(f_n, iter.c_str(), size)) {
			return false;  // bad!
		}
	}
	return true; // Good!
}

void tlx::frontend::Preprocessor::findFiles(const std::string& path)
{
	using fs = std::filesystem;
	std::string filename = "";
	try {
		if (fs::exists(path)) {
			if (fs::is_regular_file(path)) {
				filename = fs::absolute(path);
				this->process(filename);
			}
			else {
				this->writeError(tlx::frontend::PreErrors::NOT_FOUND_FILE, "File \"" + path + "\" is folder OR is not valid file");
			}
			return;
		}
		else {
			std::regex pattern(path);
			std::string base_directory = fs::path(path).parent_path().string();
			for (const auto& entry : fs::recursive_directory_iterator(base_directory)) {
				if (fs::is_regular_file(entry.status())) {
					filename = entry.path().filename().string();
					if (std::regex_match(filename, pattern))
						this->process(filename);
				}
			}
		}
	}
	catch (const fs::filesystem_error& er) {
		this->writeError(tlx::frontend::PreErrors::FILESYSTEM, er.what());
	}
}


