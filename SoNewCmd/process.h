#ifndef PROCESS_H
#define PROCESS_H
#include "utils.h"
#include "win32functions.h"

namespace SoNew {
	class Process {
	public:
		Process(DWORD dwPid);
		Process(const String &name);
		
		bool InjectDll(const String &dllName);
		//bool InjectDllAndExecFunc(const String &dllName, 
		void printProcName();

		~Process();
	private:
		HANDLE m_hProcess;
		LPVOID m_pRemoteNameAddr;
		LPVOID m_pDllFuncName;
	};
}
#endif