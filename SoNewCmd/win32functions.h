#ifndef WIN32FUNCTIONS_H
#define WIN32FUNCTIONS_H
#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include "utils.h"

namespace SoNew {
	// Process Helpers
	HANDLE GetProcessByPid(DWORD pid);
	HANDLE GetProcessByName(const String &processName);
	String GetProcessNameByHandle(HANDLE process);

	// Remote Thread & Memory Helpers
	LPVOID RemoteAllocate(HANDLE process, size_t len);
	BOOL WriteToRemoteMemory(HANDLE process, void* address, char* dllName, size_t len);

	// Various UI/Text Functions
	void PrintProcessList();
	void PrintProcessByPid(DWORD pid);
}
#endif
