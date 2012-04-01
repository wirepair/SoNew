#ifndef INJECTORCODECAVE_H
#define INJECOTRCODECAVE_H
#include "utils.h"
#include "injector.h"
#include <AsmJit/AsmJit.h>
#include <AsmJit/MemoryManager.h>
#include "remotecodegenerator.h"

using namespace AsmJit;
// Uses AsmJit to create a loader.
namespace SoNew {
	class InjectorCodeCave : public Injector {
	public:
		InjectorCodeCave(Method &injMethod);//  : Injector(injMethod) {};
		virtual LPVOID Inject(HANDLE hProcess);
		//virtual BOOL Execute(HANDLE hProcess);
		virtual BOOL Execute();
		virtual BOOL InjectAndExecute(HANDLE hProcess);
		int CreateCodeCaveLoader(Assembler &assembler);

		~InjectorCodeCave();
	protected:
		LPVOID m_remoteAddress; // set on Inject
		HANDLE m_hProcess; // set on Inject
		HANDLE m_hThread; // set on Execute
	};
}
#endif