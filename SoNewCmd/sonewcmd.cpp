#include "sonewcmd.h"

#pragma comment( lib, "psapi" )
#pragma comment( lib, "cpp-argparser" )

using namespace cppargparser;
using namespace SoNew;

int main(int argc, char *argv[], char *envp[]) {
	Process *proc = 0;
	SoNewArgumentParser argParser;
	ParsedArgument pa;
	Injector *injector;
	tcout << "SoNew Version 0.1 By Isaac Dawson" << endl;
	// do some sanity checks.
	pa = ValidateArguments(argParser, argc, argv);
		
	// We've made it this far, let's create our injection method object via the users args
	Method injectionMethod = Method(pa);
	switch(injectionMethod.m_injectionType) {
		case CRTLL:
			if (injectionMethod.m_pDllName == NULL)
				ShowError(argParser, L"Error: CreateRemoteThread & LoadLibrary Method Requires a DLL!");
			injector = new InjectorCRTLL(injectionMethod);
			break;
		case CRTWMP:
			//injector = new InjectorCRTWMP(injectionMethod);
			break;
		case CodeCave:
			//injector = new InjectorCodeCave(injectionMethod);
			break;
		case IATHooks:
			//injector = new InjectorIATHooks(injectionMethod);
			break;
		default:
			ShowError(argParser, L"Error: Unknown Injection Method");
			exit(-1);
	}
	if (injector == NULL) {
		ShowError(argParser, L"Our Injector is null.");
	}

	// setup our process object
	if (pa.hasArgument("-p"))
		proc = new Process(StringToNumber<int>(pa.getValue("-p")));
	else if (pa.hasArgument("-n"))
		proc = new Process(StringToWstring(pa.getValue("-n")));
	if (proc == 0) 
		ShowError(argParser, L"We do not have a process selected!");
	tcout << "Process: " << proc->getProcessName() << " selected." << endl;
	proc->InjectInto(*injector);
	delete injector;
	delete proc;
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