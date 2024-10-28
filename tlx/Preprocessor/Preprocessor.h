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
			DEFINE,
			INCLUDE,
			RULE
		};
		class Preprocessor {
		public:
			Preprocessor(const std::string& filename);
			~Preprocessor(void);
			std::string process(void); // if (isEmpty -> errors)
			std::vector<tlx::Error>& getErrors(void) const;
		private:
			void recursionIncludes(void);
			std::map<std::string, std::string> defines;
			std::vector<std::string> incs; // one includes file;
			std::vector<tlx::Error> errs;
			std::ifstream reading;
			std::size_t point; // "{$ $}"
			std::string buffer;
		};
	}
}
#endif