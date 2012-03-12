#include "Process.h"

namespace SoNew {

	Process::Process(DWORD dwPid) {
		this->m_hProcess = GetProcessByPid(dwPid);
	}

	Process::Process(const String &name) {
		this->m_hProcess = GetProcessByName(name);
	}

	BOOL Process::InjectInto(Injector &injector) {
		if (injector.Inject(m_hProcess)) {
			return injector.Execute(m_hProcess);
		}
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