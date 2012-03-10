#ifndef INJECTOR_H
#define INJECTOR_H
#include <windows.h>
#include "method.h"

namespace SoNew {
	class Injector {
	public:
		Injector(const Method &injMethod) : m_injMethod(injMethod) {};
		// Our injection method should return an addr of 
		// where we are injected into in the remote process
		virtual DWORD Inject() = 0; 
		// Execute our junk in their shit! Return True on success
		virtual BOOL Execute() const = 0;
	protected:
		Method m_injMethod;
	};
}
#endif