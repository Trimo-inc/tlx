#ifndef __LEXER__tlx__v2
#define __LEXER__tlx__v2

#define EXPORT __declspec(dllexport)

#include <string>

#include "./Tokens.h"

namespace tlx {

	struct Token {
		tlx::Types type;
		char* value; 
	};
	struct S1ndex
	{
		std::size_t size;
		std::size_t index;
	};
	class EXPORT Lexer {
	public:
		Lexer(void);
		~Lexer(void);
		inline void set(const std::string& data);
		tlx::Token next(void);
	private:
		inline tlx::Types getOperator(void); // if not operator return 'UNDEFINED'
		inline tlx::Types getKeyword (void); // if not keyword  return 'UNDEFINED'
		struct tlx::S1ndex search_word(const char** array, const std::size_t& SIZE_array);
		std::string getName(void);
		void skipSpace(void);
		std::size_t pos;
		std::string buffer;
		tlx::Types gets(const char** array, const tlx::Types array_t[],  const std::size_t& size);
	};

}

#endif