#include "all.h"
#include <fstream>
BOOL WINAPI DllMain(HMODULE hmod, DWORD re_to_call, LPVOID reserved)
{
	return TRUE;
}
void readLine(std::string& buff, std::ifstream& file)
{
	char ch;
	const char LF = '\n', CR = '\r';
	std::size_t count = 0;
	while (file.get(ch)) {
		buff += ch;
		if (ch == LF) {
			ch = file.peek();
			if (ch == CR)
				file.get();
			break;
		}
		else {
			if (ch == CR) {
				ch = file.peek();
				if (ch == LF) {
					file.get();
				}
				buff[buff.size() - 1] = LF;
				break;
			}
		}
		if (count >= max_lenght) {
			if (ch == ';')
				break;
		}
		count++;
	}
}

extern "C" EXPORT char* get_F(const char* filename)
{
	char* result = NULL;
	std::ifstream file{ filename, std::ios::binary };
	tlx::Lexer lexer;
	tlx::Token tk {tlx::UNKNOWN};
	if (file.is_open()) {
		std::string line;
		while (!file.eof()) {
			readLine(line, file);
			lexer.set(line);
			while (tk.type != tlx::EOF_)
				tk = lexer.next();
			line = "";
			tk.type = tlx::UNKNOWN;
		}
	}
	return result;
}



#ifdef TEST
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	return 0;
}
#endif
