#ifndef __STATIC_TLX
#define __STATIC_TLX
#include "Lexer/Lexer.h"
namespace tlx {
	enum Errors : char {
		PREPROCESSOR,
		LEXER,
		PARSER, // Syntax
		SEGMENT,
	};
	struct Interval {
		std::size_t pos1;
		std::size_t pos2;
	};
	struct Error {
		tlx::Errors type;
		std::size_t code;
		std::size_t line_n;
		tlx::Interval interval;
		char* message = NULL;
		~Error(void);
	};

	static const char* operators[]
	{
		"+", "-", "*", "\\",
		"/", "%", "++",	"--",
		"!", "NOT", "&&", "AND",
		"||", "OR", "==", "!=", 
		"<",  ">", "<=",  ">=",
		"~", "&", "|", "^",
		"<<", ">>",
		"=", "+=", "-=", "*=", "/=",
		".", ",", ";",
		"{$", "$}"
	};
	using tlx::Types;
	static const tlx::Types operators_types[]
	{
		Types::PLUS, Types::MINUS, Types::ASTERISK, Types::SLASH,
		Types::BACK_SLASH, Types::PERCENT, Types::INCREMENT, Types::DECREMENT,
		Types::NOT, Types::NOT, Types::AND, Types::AND,
		Types::OR, Types::OR, Types::EQUAL, Types::N_EQUAL,
		Types::LT, Types::GT, Types::LE, Types::GE,
		Types::B_NOT, Types::B_AND, Types::B_OR, Types::B_XOR,
		Types::B_LSHIFT, Types::B_RSHIFT,
		Types::ASSIGN, Types::ADD_ASSIGN, Types::SUB_ASSIGN, Types::MULT_ASSIGN, Types::DIV_ASSIGN,
		Types::POINT, Types::COMMA, Types::SEMICOLON,
		Types::BLOCK_START, Types::BLOCK_END
	};

	static const char* keywords[] =
	{
		"static",
		"func",
		"sizeof",
		"const",
		"if",
		"then",
		"else",
		"while",
		"continue",
		"break",
		"for",
		"in",
		"is",
		"return",
		"end",
		"true",
		"false",
		"null"
	};
#ifdef NULL
#undef NULL
#endif
	static const tlx::Types keywords_types[]
	{
		Types::STATIC,
		Types::FUNC,
		Types::SIZEOF,
#ifdef CONST
#undef CONST
#endif
		Types::CONST,
		Types::IF, Types::THEN, Types::ELSE,
		Types::WHILE, Types::CONTINUE, Types::BREAK,
		Types::FOR, Types::IN, Types::IS, Types::RETURN,
		Types::END, Types::TRUE, Types::FALSE, Types::NULL
	};
#ifndef NULL
#define NULL 0
#endif
#ifndef CONST
#define CONST const
#endif
	constexpr std::size_t size_operators = (sizeof(operators) / sizeof(*operators));
	constexpr std::size_t size_keywords  = (sizeof(keywords)  / sizeof(*keywords));
}

namespace tlx
{
	static void setPath(const char* fullpath);
	static std::string fullpath_dir;
}

#endif