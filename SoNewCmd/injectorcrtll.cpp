#include "injectorcrtll.h"

namespace SoNew {

	InjectorCRTLL::InjectorCRTLL(const Method &injMethod) : Injector(injMethod) {
		m_injectionMethod = injMethod;
		//tcout << "We got a Dll of: " << *m_injectionMethod.m_pDllName << endl;
	}
	LPVOID InjectorCRTLL::Inject(HANDLE hProcess) {
		m_hProcess = hProcess; // set our process member.

		tcout << "Injecting via CreateRemoteThread & LoadLibrary" << endl;
		size_t len = m_injectionMethod.m_pDllName->length()+1; // add one for null
		// allocate and set our address
		m_remoteAddress =  RemoteAllocate(hProcess, len);
		if (m_remoteAddress == 0) {
			PrintLastErrorMessage(L"[*] Error remotely allocating space");
			return 0;
		}
		tcout << "[*] Allocated " << len << " bytes at: " << m_remoteAddress << endl;
		BOOL ret = WriteToRemoteMemory(hProcess, m_remoteAddress, narrow(*m_injectionMethod.m_pDllName), len);
		if (ret == FALSE) {
			PrintLastErrorMessage(L"[*] Error Writing To Remote Process");
			return 0;
		}	
		tcout << "[*] Wrote our DLL into the remote process at " << m_remoteAddress << endl;

		return m_remoteAddress;
	}
	BOOL InjectorCRTLL::Execute() {
		PTHREAD_START_ROUTINE loadLibraryAddress = LoadLibraryAddress();
		if (loadLibraryAddress == NULL) {
			tcout << "[*] Error: LoadLibrary Address is NULL." << endl;
			return false;
		}
		tcout << "[*] LoadLibrary is at: " << loadLibraryAddress << endl;
		tcout << "[*] Creating Remote Thread..." << endl;
		m_hThread = CreateRemoteThread(m_hProcess, 
									   NULL, 
									   0, 
									   loadLibraryAddress, 
									   m_remoteAddress, 
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

	BOOL InjectorCRTLL::InjectAndExecute(HANDLE hProcess) {
		LPVOID result = this->Inject(hProcess);
		if (result != NULL)
			return this->Execute();
		return false;
	}

	InjectorCRTLL::~InjectorCRTLL() {
		if (m_remoteAddress != NULL)
			VirtualFreeEx(m_hProcess, m_remoteAddress, 0, MEM_RELEASE);
		if (m_hThread != NULL)
			CloseHandle(m_hThread);
		if (m_hProcess != NULL)
			CloseHandle(m_hProcess);
	}
}