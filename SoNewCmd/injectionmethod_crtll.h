#ifndef INJM_CRTLL_H
#define INJM_CRTLL_H
#include "utils.h"
#include "injector.h"
// CreateRemoteThread and LoadLibrary our selves into a remote process
// Takes a DLL and alternatively an exported function name to call 
// on Execute();
namespace SoNew {
	class InjmCrtLL : public Injector {
	public:
		InjmCrtLL::InjmCrtLL(const Method &injMethod);//  : Injector(injMethod) {};
		virtual DWORD Inject();
		virtual BOOL Execute();
	protected:
		Method m_injectionMethod;
	};
}
#endif