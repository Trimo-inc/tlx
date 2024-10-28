#ifndef __ALL__DLL
#include <Windows.h>
#include <TlHelp32.h>
#define __ALL__DLL



BOOL WINAPI DllMain(HMODULE hmod, DWORD re_to_call, LPVOID reserved);

#include "tlx/Lexer/Lexer.h"
#include <fstream>

const unsigned short max_lenght = 528;
/*
@brief ������ ��������� ����, ��������������� �� '\\n' <-> '\r' <-> '\\n\r' <-> '\r\\n'
@brief �� ������ max_lenght ��������, ���� �� �������� ����� ������
@brief ���� ���� � ���� ������, �� ����� max_lenght ������, ���� �� �������� ";"
*/
void readLine(std::string& buff, std::ifstream& file);
extern "C" EXPORT char* get_F(const char* filename);


#define TRUE 1
#define FALSE 0
#define IN


#ifdef TEST
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd);

#endif
#endif