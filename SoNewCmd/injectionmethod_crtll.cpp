#include "injectionmethod_crtll.h"

namespace SoNew {

	InjmCrtLL::InjmCrtLL(const Method &injMethod) : Injector(injMethod) {
		m_injectionMethod = injMethod;
		tcout << "We got a Dll of: " << *m_injectionMethod.m_pDllName << endl;
	}
	DWORD InjmCrtLL::Inject() {
		DWORD x = 0xf32f2f4;
		tcout << "Injecting..." << x << endl;
		return x;
	}
	BOOL InjmCrtLL::Execute() {
		tcout << "Executing..." << endl;
		return true;
	}

}