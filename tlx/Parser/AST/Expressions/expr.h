#ifndef __EXPRESSIONS__TLX
#define __EXPRESSIONS__TLX

#include "../ast.h"

namespace tlx {
	namespace ast {
		class Literal : public tlx::ast::base::Expression {
		public:
			Literal(const tlx::Types& type);
			char& getInt8(void);
			short& getInt16(void);
			int& getInt32(void);
			float& getFloat(void);
			double& getDoubleFloat(void);
			std::string& getString(void);
		protected:
			std::string value; // struct Any;
		};
	}
}

#endif