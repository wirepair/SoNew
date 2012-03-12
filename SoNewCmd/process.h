#ifndef PROCESS_H
#define PROCESS_H
#include "utils.h"
#include "injector.h"
#include "win32functions.h"

namespace SoNew {
	class Process {
	public:
		Process(DWORD dwPid);
		Process(const String &name);
		
		BOOL InjectInto(Injector &injector);
		//bool InjectDllAndExecFunc(const String &dllName, 
		void printProcessName();
		String getProcessName();

		~Process();
	private:
		HANDLE m_hProcess;
		LPVOID m_pRemoteNameAddr;
		LPVOID m_pDllFuncName;
	};
}
#endif