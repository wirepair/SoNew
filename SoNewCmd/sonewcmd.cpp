#include "sonewcmd.h"

#pragma comment( lib, "psapi" )
#pragma comment( lib, "cpp-argparser" )

using namespace cppargparser;
using namespace SoNew;


int main(int argc, char *argv[], char *envp[]) {
	ParsedArgument pa;

	tcout << "SoNew Version 0.1 By Isaac Dawson" << endl;
	// do some sanity checks.
	pa = ValidateArguments(argc, argv);
		
	// We've made it this far, let's create our injection method object via the users args
	Method injectionMethod = Method(pa);
	tcout << injectionMethod.m_injectionType << endl;
	Process proc(StringToNumber<int>(pa.getValue("-p")));
	proc.printProcName();
	return 0;
}

/*
	String exe = L"chrome.exe";
	Process proc = Process(exe);
	int injtype = 1;

	switch(injtype) {
		case CRTLL:
			{
				tcout << "CreateRemoteThread & LoadLibrary Selected." << endl;
				Method injMethod(L"C:\\Research\\SoNew\\Debug\\SoNewTestDll.dll");
				tcout << *injMethod.m_dllName << endl;
			}
			break;
		default:
			tcout << "Error unknown injection type selected. " << endl;
			exit(-2);
	}
//HMODULE hMod = LoadLibrary(L"SoNewTestDll.dll");
//FARPROC test = GetProcAddress(hMod, "RunTest");
//test();
*/