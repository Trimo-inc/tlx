#include "./Preprocessor.h"
#include "../../all.h"

#include <regex>


tlx::frontend::Preprocessor::Preprocessor(const std::string& filename) : file_wr(filename + ".pre")
{
	this->incs.push_back(filename);
}
tlx::frontend::Preprocessor::~Preprocessor(void)
{
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
	std::size_t point = 0;
	while (!reading.eof()) {
		const auto pry = this->read(point, reading);
		if (!reading.good()) {
			std::string msg = "The file reached its end before it found the keyword \"" + tlx::frontend::Property_toString(pry) + "\"";
			this->writeError(tlx::frontend::PreErrors::EOF_OFFSET, msg);
		}
		this->recursionIncludes(pry, reading);
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
		
		this->recursionIncludes(buffer, file_read);
	}

}

void tlx::frontend::Preprocessor::recursionIncludes(const tlx::frontend::Property& prop, std::ifstream& file_rd)
{
	char r, dk;
	std::string buffer = "";
	char count_endl = 0; // It're "\\n" | "\r"
	const char q = '\'', dq = '\"';
	switch (prop)
	{
		case tlx::frontend::Property::INCLUDE: {
			while (file_rd.get(r)) {
				buffer += r;
				if (r != ' ') {

				}
				if (r == q || r == dq) {
					dk = q;
				}
			}
			break;
		}
		case tlx::frontend::Property::RULE: {

			break;
		}
	}
}

void tlx::frontend::Preprocessor::recursionIncludes(const std::string& buffer, std::ifstream& file_rd)
{
	std::size_t posi = 0, point = 0; // {$ $};
	const char dollar = '$';
	const char* include = "include";
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
						while (posi <= buffer.size() && (buffer[posi] != dk) ) {
							filename += buffer[posi++];
						}
						if (buffer[posi] != dk) {
							std::string dk_str = dk + "";
							this->writeError(tlx::frontend::PreErrors::SYNTAX, "Expected " + dk_str + " symbol");
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

tlx::frontend::Property tlx::frontend::Preprocessor::read(std::size_t& point, std::ifstream& file_rd)
{
	std::size_t pos = 0;
	tlx::frontend::Property _property{ tlx::frontend::Property::RULE }; // magic constants // Чтобы убрать лишний break;
	const char* include = "include", *rule = "rule";
	char r, offset_ptr_file = 4; // is lenght string - 'rule' (AND optimization to 3 if (in while))
	std::string buffer = "";
	while (file_rd.get(r)) 
	/* Перемещает указатель файла вперёд, так что файл не стоит на месте */
	{
		buffer += r;
		if (point) { // reading 'include' & 'rule' | '{$' | '$}'
			this->begin0Rend(buffer, point, pos);
			if (buffer.find(include) != std::string::npos) {
				_property = tlx::frontend::Property::INCLUDE; 
				offset_ptr_file = 8; // 8 is lenght string - 'include'
				break;
			}
			else
				if (buffer.find(rule) != std::string::npos) 
					break;
				
		}
		else {
			// reading '{$'
			this->begin0Rend(buffer, point, pos);
		}
		this->file_wr << r;
	}
	file_rd.seekg(offset_ptr_file, std::ios::cur);
	return _property;
}

void tlx::frontend::Preprocessor::begin0Rend(const std::string& buffer, std::size_t& point, std::size_t& posix)
{
	const char max_lenght = 3, dollar = '$';
	if (posix >= max_lenght) {
		const std::size_t posix1 = posix + 1;
		if (buffer[posix] == '{' && buffer[posix1] == dollar && buffer[posix1 + 1] != dollar)
			point++;
		else
			if (point && (buffer[posix] == dollar && buffer[posix1] == '}'))
				point--;
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
		if (!strncmp(p_n, iter.c_str(), size)) {
			return false;  // bad!
		}
	}
	return true; // Good!
}

std::string tlx::frontend::Property_toString(const tlx::frontend::Property& pr)
{
	std::string ret = "";
	switch (pr)
	{
		case tlx::frontend::Property::INCLUDE: {
			ret = "include";
			break;
		}
		case tlx::frontend::Property::RULE: {
			ret = "rule";
			break;
		}
	}
}
