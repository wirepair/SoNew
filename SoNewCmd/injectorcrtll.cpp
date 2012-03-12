#include "injectorcrtll.h"

namespace SoNew {

	InjectorCRTLL::InjectorCRTLL(const Method &injMethod) : Injector(injMethod) {
		m_injectionMethod = injMethod;
		//tcout << "We got a Dll of: " << *m_injectionMethod.m_pDllName << endl;
	}
	LPVOID InjectorCRTLL::Inject(HANDLE hProcess) {
		tcout << "Injecting via CreateRemoteThread & LoadLibrary" << endl;
		size_t len = m_injectionMethod.m_pDllName->length()+1; // add one for null
		if (m_injectionMethod.m_pFunctionName != 0) {
			len += m_injectionMethod.m_pFunctionName->length()+1; // add one for null
		}
		return RemoteAllocate(hProcess, len);
	}
	BOOL InjectorCRTLL::Execute(HANDLE hProcess) {
		tcout << "Executing..." << endl;
		return true;
	}

	BOOL InjectorCRTLL::InjectAndExecute(HANDLE hProcess) {
		LPVOID result = this->Inject(hProcess);
		return this->Execute(hProcess);
	}

}