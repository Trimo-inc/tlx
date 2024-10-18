#ifndef __PARSER__TLX
#define __PARSER__TLX
#include "../Lexer/Lexer.h"
#include <fstream>
namespace tlx {
	struct Error {
		unsigned long long CODE = 0;
		char* about = NULL;
	};
	
	class EXPORT Parser {
	public:
		Parser(const std::string& path_to_file);
		bool render(void); // if not error to true else false
		struct tlx::Error& LastError(void);
	private:
		std::fstream file;  // reading file
		tlx::Lexer lexer; 
		struct tlx::Error lastErr;
	};


}
#endif