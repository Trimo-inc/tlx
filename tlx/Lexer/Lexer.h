#ifndef __LEXER__tlx__v2
#define __LEXER__tlx__v2

#define EXPORT __declspec(dllexport)

#include <string>

#ifdef NULL
#undef NULL
#endif


namespace tlx {
	enum Types : char {
		// Keywords
		BLOCK_START, // {$
		BLOCK_END,	 // $}
		END,
		IF,
		THEN,
		ELSE,
		WHILE,
		BREAK,
		CONTINUE,
		FUNC,
		RETURN,
		FOR,
#ifdef IN
#undef IN
#endif
		IN,
		IS,
		// Keyword types
#ifdef TRUE
#undef TRUE
#endif
		TRUE,
#ifdef FALSE
#undef FALSE
#endif
		FALSE,
		NULL,
		STATIC,
		SIZEOF,
#ifdef CONST
#undef CONST
#endif
		CONST,
#ifndef CONST
#define CONST const
#endif
		NAME, // example: 'variable = 9;' -> NAME is "variable"
		// Math operators
		PLUS,		// '+'
		MINUS,		// '-'
		ASTERISK,	// '*'
		SLASH,		// '\'
		BACK_SLASH, // '/'
		PERCENT,	// '%'
		INCREMENT, // '++'
		DECREMENT, // '--'
		NOT, // 'not' || '!'
		AND, // 'and' || '&&'
		OR,  // 'or'  || '||'
		// Programming operators and math 
		EQUAL, // '=='
		N_EQUAL, // '!='
		LT, // '<'
		GT, // '>'
		LE, // '<='
		GE, // '>='
		// Bitwise
		B_NOT, // '~'
		B_AND, // '&'
		B_OR,  // '|'
		B_XOR, // '^'
		B_LSHIFT, // '<<'
		B_RSHIFT, // '>>'
		// Assignments
		ASSIGN, // '='
		ADD_ASSIGN, // '+='
		SUB_ASSIGN, // '-='
		MULT_ASSIGN,// '*='
		DIV_ASSIGN, // '/='
		// Special symbols
		POINT, // '.'
		COMMA, // ','
		SEMICOLON, // ';'
		// SPECIAL
		UNKNOWN,
		UNDEFINED, // Type is 'UNDEFINED'
		// EOF for buffer
		EOF_
	};
#define NULL 0
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