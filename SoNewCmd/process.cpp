#include "Process.h"

namespace SoNew {

	Process::Process(DWORD dwPid) {
		this->m_hProcess = GetProcessByPid(dwPid);
	}

	Process::Process(const String &name) {
		this->m_hProcess = GetProcessByName(name);
	}

	BOOL Process::InjectInto(Injector &injector) {
		LPVOID address = injector.Inject(m_hProcess);
		if (address != 0) {
			return injector.Execute();
		}
		tcout << "[*] ERROR: Injection Failed." << endl;
		return false;
	}

	void Process::printProcessName() {
		if (this->m_hProcess == NULL) {
			tcout << "We don't have a handle to any process." << endl;
		} else {
			tcout << "We have a handle to: " << GetProcessNameByHandle(this->m_hProcess) << endl;
		}
	}

	String Process::getProcessName() {
		return GetProcessNameByHandle(this->m_hProcess);
	}

	Process::~Process() {
		CloseHandle(this->m_hProcess);
	}
}