#include "Lexer.h"
#include "../static.h"
#include <iostream>

tlx::Lexer::Lexer(void) : pos(0) {}
tlx::Lexer::~Lexer(void) { buffer.~basic_string(); }

inline void tlx::Lexer::set(const std::string& data)
{
	this->buffer = data;
	this->pos = 0;
}

tlx::Token tlx::Lexer::next(void)
{
	tlx::Token token{ tlx::Types::UNKNOWN, nullptr };
	if (this->pos < this->buffer.size()) {
		this->skipSpace();
		tlx::Types type = this->getOperator();
		if (type == tlx::Types::UNDEFINED) {
			// Construction is not OPERATOR
			type = this->getKeyword();
			if (type == tlx::Types::UNDEFINED) {
				std::string name = this->getName();
				size_t size_name = name.size() + 1;
				if (!name.empty() && size_name != std::string::npos) {
					type = tlx::Types::NAME;
					token.value = new char[size_name];
					name.copy(token.value, size_name - 1);
					token.value[size_name] = '\0';
				}
			}
		}
		token.type = type;



	}
	else token.type = tlx::Types::EOF_;
	return token;
}



inline tlx::Types tlx::Lexer::getOperator(void)
{
	return gets(tlx::operators, tlx::operators_types, tlx::size_operators);
}
inline tlx::Types tlx::Lexer::getKeyword(void)
{
	return gets(tlx::keywords, tlx::keywords_types, tlx::size_keywords);
}



struct tlx::S1ndex tlx::Lexer::search_word(const char** array, const std::size_t& SIZE_array)
{
	struct tlx::S1ndex si { 0 };
	std::string w;
	const size_t size_line = this->buffer.size();
	for (unsigned short i = 0u; i < SIZE_array; i++) {
		si.size = std::strlen(array[i]);
		if (si.size < size_line) {
			w = this->buffer.substr(this->pos, si.size);
			if (!strncmp(w.c_str(), array[i], si.size)) {
				si.index = i;
				this->pos += si.size;
				break;
			}
		}
		si.size = 0;
	}
	return si;
}
#include <cctype>
std::string tlx::Lexer::getName(void)
{
	std::string name;
	char down = '_';
	if (
		std::isalpha(static_cast<unsigned char>(this->buffer[this->pos]))
		|| this->buffer[this->pos] == down
		) {
		name += this->buffer[this->pos++];
		while (
			std::isalnum(static_cast<unsigned char>(this->buffer[this->pos]))
			|| this->buffer[this->pos] == down
			)
			name += this->buffer[this->pos++];
	}
	return name;
}
void tlx::Lexer::skipSpace(void)
{
	while (this->pos < this->buffer.size() && isspace(static_cast<unsigned char>(this->buffer[this->pos])))
	{
		this->pos++;
	}
}
tlx::Types tlx::Lexer::gets(const char** array, const tlx::Types array_t[], const std::size_t& size)
{
	struct tlx::S1ndex S = this->search_word(array, size);
	tlx::Types type = tlx::Types::UNDEFINED;
	if (S.size)
		type = array_t[S.index];
	return type;
}

 