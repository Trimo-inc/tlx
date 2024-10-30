#ifndef TOKENS_TLX__v1
#define TOKENS_TLX__v1

#ifdef IN
#undef IN
#endif

#ifdef CONST
#undef CONST
#endif

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

#ifdef CONST
#undef CONST
#endif

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
		IN,
		IS,
		// Keyword types
		TRUE,
		FALSE,
		NULL,
		STATIC,
		SIZEOF,
		CONST,
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
}

#ifndef CONST
#define CONST const
#endif

#ifndef NULL
#define NULL 0
#endif


#endif