// AsmJit-Ext - Remote Code Generator.

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#include <AsmJit/Build.h>
#include "RemoteCodeGenerator.h"
namespace AsmJit {

	RemoteCodeGenerator::RemoteCodeGenerator(HANDLE hProcess) :
	  _hProcess(hProcess),
	  _memoryManager(hProcess)
	{
		// We are patching another process so set keep-virtual-memory property to 
		// true.
		_memoryManager.setKeepVirtualMemory(true);
	}

	RemoteCodeGenerator::~RemoteCodeGenerator()
	{
	}

	uint32_t RemoteCodeGenerator::generate(void** dest, Assembler* assembler) {
		// Disallow empty code generation.
		sysuint_t codeSize = assembler->getCodeSize();
		if (codeSize == 0)
		{
			*dest = NULL;
			return AsmJit::ERROR_NO_FUNCTION;
		}

		// Allocate temporary memory where the code will be stored and relocated.
		void* codeData = ASMJIT_MALLOC(codeSize);
		if (codeData == NULL)
		{
			*dest = NULL;
			return ERROR_NO_HEAP_MEMORY;
		}

		// Memory will be never freed, use pernament allocation.
		//
		// NOTE: This allocates memory of the hProcess, not our process.
		void* processMemPtr = _memoryManager.alloc(codeSize, MEMORY_ALLOC_PERMANENT);
		if (processMemPtr == NULL)
		{
			ASMJIT_FREE(codeData);

			*dest = NULL;
			return ERROR_NO_VIRTUAL_MEMORY;
		}

		// Relocate and write the code to the process memory.
		assembler->relocCode(codeData, (sysuint_t)processMemPtr);
		WriteProcessMemory(_hProcess, processMemPtr, codeData, codeSize, NULL);

		ASMJIT_FREE(codeData);
		*dest = processMemPtr;
		return ERROR_NONE;
	}

} // AsmJit namespace
