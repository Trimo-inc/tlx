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
		std::string Property_toString(const tlx::frontend::Property& pr);
		enum PreErrors : char {
			OPEN_OUT,
			OPEN_IN,
			NOT_OPEN_FILE,
			NOT_FOUND_FILE,
			EOF_OFFSET,
			SYNTAX,
			FILESYSTEM,
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
			void recursionIncludes(const tlx::frontend::Property& prop, std::ifstream& file_rd);
			void recursionIncludes(const std::string& buffer, std::ifstream& file_rd); // delete func
			/*
			@brief Читает до ключевых слов 'rule' и 'include', записывая всё в файл
			@return Что прочитал тип rule или include
			*/
			tlx::frontend::Property read(std::size_t& point, std::ifstream& file_rd);
			void begin0Rend(const std::string& buffer, std::size_t& point, std::size_t& posix);

			std::vector<std::string> incs; // one includes file;
			std::vector<tlx::Error> errs;
			void writeError(const tlx::frontend::PreErrors& n);
			void writeError(const tlx::frontend::PreErrors& code, const std::string& data);
			std::ofstream file_wr; // One file to writen info
			bool isNotFoundFilename(const std::string& name);
			void findFiles(const std::string& path);
		};
	}
}
#endif