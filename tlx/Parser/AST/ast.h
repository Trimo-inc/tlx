#ifndef __AST__GENERAL__tlx
#define __AST__GENERAL__tlx

#include "../../Lexer/Lexer.h"


namespace tlx {
	namespace ast {
		namespace base {
			class Expression {
			public:
				tlx::Types type;
			protected:
				virtual void evaluate(void) const = 0;
			};
			class Statement {
			public:
				Statement(const tlx::Types& type);
				const tlx::Types& getType() const;
				virtual void execute(void) = 0;
			protected:
				tlx::Types type;
			};
		}
	}
}


#endif