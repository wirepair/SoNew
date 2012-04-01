#include "injectorcodecave.h"

namespace SoNew {
	InjectorCodeCave::InjectorCodeCave(Method &injMethod) : Injector(injMethod) {
		m_injectionMethod = injMethod;
		tcout << "We got a Dll of: " << *m_injectionMethod.m_pDllName << endl;
		if (m_injectionMethod.m_pFunctionName != NULL) {
			tcout << "We have a function name of: " << *m_injectionMethod.m_pFunctionName << endl;
		} else {
			m_injectionMethod.m_pFunctionName = new String(L"DllMain");
		}
	}

	LPVOID InjectorCodeCave::Inject(HANDLE hProcess) {
		m_hProcess = hProcess;
		tcout << "Injecting via CodeCave (Uses WriteProcessMemory & CreateRemoteThread + AsmJit)" << endl;
		RemoteCodeGenerator codeGenerator(m_hProcess);
		Assembler assembler;
		int ret = CreateCodeCaveLoader(assembler);
		if (ret == 0) {
			codeGenerator.generate(&m_remoteAddress, &assembler);
		}
		return m_remoteAddress;
	}

	BOOL InjectorCodeCave::Execute() {
		tcout << "[*] CodeCave Injector Creating Remote Thread..." << endl;
		m_hThread = CreateRemoteThread(m_hProcess, 
									   NULL, 
									   0, 
									   (LPTHREAD_START_ROUTINE)m_remoteAddress, 
									   0, 
									   0, 
									   NULL);
		if (m_hThread == NULL) {
			PrintLastErrorMessage(L"[*] Error: CreateRemoteThread Failed");
			return false;
		}
		tcout << "[*] Remote Thread Created." << endl;
		WaitForSingleObject(m_hThread, INFINITE);
		return true;
	}

	BOOL InjectorCodeCave::InjectAndExecute(HANDLE hProcess) {
		LPVOID result = this->Inject(hProcess);
		if (result != NULL)
			return this->Execute();
		return false;
	}

	int InjectorCodeCave::CreateCodeCaveLoader(Assembler &a) {
		HMODULE kernel = GetModuleHandle(L"kernel32");	// need kernel32's base address
		FARPROC load_library = GetProcAddress(kernel, "LoadLibraryA"); // need ll's address
		FARPROC get_proc_address = GetProcAddress(kernel, "GetProcAddress"); // heh :>.
		if (load_library == NULL) {
			printf("load_library is null: %d",GetLastError());
			return -1;
		}
		if (get_proc_address == NULL) {
			printf("get_proc_address is null: %d",GetLastError());
			return -1;
		}
		FileLogger logger(stderr);
		a.setLogger(&logger);
		{
			Label L_lib = a.newLabel();
			Label L_start = a.newLabel();
			Label L_funcname = a.newLabel();
			Label L_callfunc = a.newLabel();
			Label L_exit = a.newLabel();
			
			// Prolog.
			a.push(ebp);
			a.mov(ebp, esp);
			a.jmp(L_lib);						// jmp down to where our lib/dll is.
			a.bind(L_start);					// oh hai again!
			// Start.
			// just to show eax contains addr (next two calls not needed)
			//a.pop(eax);						// address of our dll.
			//a.push(eax);						// push on to stack for ll call
			a.call((sysint_t)load_library);		// load our dll
			a.cmp(eax, 0);						// module should be stored in eax.
			a.je(L_exit);						// make sure we have a valid module handle
			a.mov(edx, eax);					// store module in edx
			a.jmp(L_funcname);					// get the exported_func's address
			a.bind(L_callfunc);
			// just to show eax contains addr (next two calls not needed)
			//a.pop(eax);						// the name of our exported func
			//a.push(eax);						// push name of our exported func
			a.push(edx);						// push addr of our dll
			a.call((sysint_t)get_proc_address); // get exported_func's addr.
			a.cmp(eax, 0);						// func should be stored in eax.
			a.je(L_exit);						// if not bomb out
			a.call(eax);						// and call it!		
			// Epilog.
			a.bind(L_exit);
			a.mov(esp, ebp);
			a.pop(ebp);
			a.ret();
			// our "data" section
			a.bind(L_lib);
			a.call(L_start);
			// write our dll path as data.

			size_t dll_len = m_injectionMethod.m_pDllName->length()+1;
			a.data(narrow(*m_injectionMethod.m_pDllName), dll_len);
			a.bind(L_funcname);
			a.call(L_callfunc);
			// write our exported function name as data
			size_t func_len = m_injectionMethod.m_pFunctionName->length()+1;

			a.data(narrow(*m_injectionMethod.m_pFunctionName), func_len);
		}
		return 0;
	}

}