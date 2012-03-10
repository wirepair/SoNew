#include "win32functions.h"

namespace SoNew {

	HANDLE GetProcessByPid(DWORD dwPid) {
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
		return hProcess;
	}

	HANDLE GetProcessByName(const String &strProcName) {
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		HANDLE hProcess;

		unsigned int i;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
			tcout << "Error reading processes, are our permissions gimped?" << endl;
			exit(-1);
		}

		cProcesses = cbNeeded / sizeof(DWORD);
		for (i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) {
				hProcess = GetProcessByPid(aProcesses[i]);
				if (hProcess == NULL)
					continue;
				String name = GetProcessNameByHandle(hProcess);
				if (name == strProcName) {
					return hProcess;
				}
				CloseHandle(hProcess);
			}
		}
		tcout << "Error no process found with name: " << strProcName << endl;
		exit(-1);
	}

	String GetProcessNameByHandle(HANDLE hProcess) {
		TCHAR szProcessName[MAX_PATH];
		HMODULE hMod;
		DWORD cbNeeded;
		
		if (hProcess == NULL) {
			return NULL;
		}
		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
		}
		return static_cast<String>(szProcessName);
	}

	// prints out the process name or <unknown> and PID.
	void PrintProcessNameAndId(DWORD processId) {
		TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
		if (NULL != hProcess) {
			HMODULE hMod;
			DWORD cbNeeded;
			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR));
			}
		}
		tcout << szProcessName << "\t\t= (PID: " << processId << ")" << endl;
		CloseHandle(hProcess);
	}
	// prints out a process list.
	void PrintProcessList() {
		tcout << "[*] Printing Process List:" << endl;
		DWORD aProcesses[1024], cbNeeded, cProcesses;
		unsigned int i;
		if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) {
			return;
		}
		cProcesses = cbNeeded / sizeof(DWORD);
		
		for (i = 0; i < cProcesses; i++) {
			if (aProcesses[i] != 0) {
				PrintProcessNameAndId(aProcesses[i]);
			}
		}
	}

	LPVOID RemoteAllocate(HANDLE hProcess, size_t len) {
		return VirtualAllocEx(hProcess, NULL, len, MEM_COMMIT, PAGE_READWRITE);
	}

	BOOL WriteToRemoteMemory(HANDLE hProcess, void* pAddr, char* szDllName, size_t len) {
		return WriteProcessMemory(hProcess, &pAddr, (LPCVOID)szDllName, len, NULL);
	}
}