#ifndef INJECTORCRTLL_H
#define INJM_CRTLL_H
#include "utils.h"
#include "injector.h"

// CreateRemoteThread and LoadLibrary our selves into a remote process
// Takes a DLL and alternatively an exported function name to call 
// on Execute();
namespace SoNew {
	class InjectorCRTLL : public Injector {
	public:
		InjectorCRTLL(const Method &injMethod);//  : Injector(injMethod) {};
		virtual DWORD Inject();
		virtual BOOL Execute();
		virtual BOOL InjectAndExecute();
	protected:
		Method m_injectionMethod;
	};
}
#endif