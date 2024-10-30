#ifndef __ALL__DLL
#include <Windows.h>
#include <TlHelp32.h>
#define __ALL__DLL



BOOL WINAPI DllMain(HMODULE hmod, DWORD re_to_call, LPVOID reserved);

#include "tlx/Lexer/Lexer.h"
#include <fstream>

const unsigned short max_lenght = 528;
/*
@brief Читает построчно файл, заканчивающийся на '\\n' <-> '\r' <-> '\\n\r' <-> '\r\\n'
@brief Он читает max_lenght символов, пока не встретит конец строки
@brief Если файл в одну строку, то после max_lenght читает, пока не встретит ";"
*/
void readLine(std::string& buff, std::ifstream& file);
extern "C" EXPORT char* get_F(const char* filename);


#define TRUE 1
#define FALSE 0
#define IN

bool isspace(const char s);

#ifdef TEST
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd);

#endif
#endif