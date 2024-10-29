#ifndef PREPROCESSOR_TLX__v1
#define PREPROCESSOR_TLX__v1
#include <string>
#include <vector>
#include <map>
#include <fstream>

#include "../static.h"
namespace tlx {
	namespace frontend {
		enum Property : char {
			INCLUDE,
			RULE
		};
		enum PreErrors : char {
			OPEN_OUT,
			OPEN_IN,
			NOT_OPEN_FILE,
			NOT_FOUND_FILE,
			RECURSION_LIMIT
		};
		class Preprocessor {
		public:
			Preprocessor(const std::string& filename);
			~Preprocessor(void);
			std::string process(void); // if (isEmpty -> errors)
			std::vector<tlx::Error>& getErrors(void) const;
		private:
			void process(const std::string& filename); 
			void recursionIncludes(const std::string& buffer, std::ifstream& file_rd);
			std::map<std::string, std::string> defines;
			std::vector<std::string> incs; // one includes file;
			std::vector<tlx::Error> errs;
			void writeError(const tlx::frontend::PreErrors& n);
			void writeError(const tlx::frontend::PreErrors& code, const std::string& data);
			std::ofstream file_wr; // One file to writen info
			
		};
	}
}
#endif