#ifndef INJECTOR_H
#define INJECTOR_H
#include <windows.h>
#include "method.h"

namespace SoNew {
	class Injector {
	public:
		Injector(const Method &injMethod) : m_injectionMethod(injMethod) {};
		// Our injection method should return an addr of 
		// where we are injected into in the remote process
		virtual LPVOID Inject(HANDLE hProcess) = 0; 
		// Execute our junk in their shit! Return True on success
		//virtual BOOL Execute(HANDLE hProcess);
		virtual BOOL Execute() = 0;
		virtual BOOL InjectAndExecute(HANDLE hProcess) = 0;
	protected:
		Method m_injectionMethod;
	};
}
#endif