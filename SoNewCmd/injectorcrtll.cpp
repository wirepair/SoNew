#include "injectorcrtll.h"

namespace SoNew {

	InjectorCRTLL::InjectorCRTLL(const Method &injMethod) : Injector(injMethod) {
		m_injectionMethod = injMethod;
		tcout << "We got a Dll of: " << *m_injectionMethod.m_pDllName << endl;
	}
	DWORD InjectorCRTLL::Inject() {
		DWORD x = 0xf32f2f4;
		tcout << "Injecting..." << x << endl;
		return x;
	}
	BOOL InjectorCRTLL::Execute() {
		tcout << "Executing..." << endl;
		return true;
	}

	BOOL InjectorCRTLL::InjectAndExecute() {
		DWORD result = this->Inject();
		return this->Execute();
	}

}