#include "Process.h"

namespace SoNew {

	Process::Process(DWORD dwPid) {
		this->m_hProcess = GetProcessByPid(dwPid);
	}

	Process::Process(const String &name) {
		this->m_hProcess = GetProcessByName(name);
	}

	bool Process::InjectDll(const String &strDllName) {
		size_t len = strDllName.length();
		this->m_pRemoteNameAddr = RemoteAllocate(this->m_hProcess, len);
		char *dll = narrow(strDllName);
		WriteToRemoteMemory(this->m_hProcess, this->m_pRemoteNameAddr, dll, len);
		return true;
	}

	void Process::printProcName() {
		if (this->m_hProcess == NULL) {
			tcout << "We don't have a handle to any process." << endl;
		} else {
			tcout << "We have a handle to: " << GetProcessNameByHandle(this->m_hProcess) << endl;
		}
	}

	Process::~Process() {
		CloseHandle(this->m_hProcess);
	}
}