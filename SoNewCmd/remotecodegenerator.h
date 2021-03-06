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

// [Guard]
#ifndef _ASMJIT_EXT_REMOTECODEGENERATOR_H
#define _ASMJIT_EXT_REMOTECODEGENERATOR_H

#include <AsmJit/Build.h>
#include <AsmJit/AsmJit.h>
// [Dependencies]
#include <AsmJit/CodeGenerator.h>
#include <AsmJit/MemoryManager.h>

namespace AsmJit {

// ============================================================================
// [AsmJit::RemoteCodeGenerator]
// ============================================================================

//! @brief Code generator is core class for changing behavior of code generated
//! by @c Assembler or @c Compiler.
struct RemoteCodeGenerator : public CodeGenerator
{
  // --------------------------------------------------------------------------
  // [Construction / Destruction]
  // --------------------------------------------------------------------------
 
  //! @brief Create a @c RemoteCodeGenerator instance for @a hProcess.
  RemoteCodeGenerator(HANDLE hProcess);
  //! @brief Destroy the @c RemoteCodeGenerator instance.
  virtual ~RemoteCodeGenerator();

  // --------------------------------------------------------------------------
  // [Accessors]
  // --------------------------------------------------------------------------

  //! @brief Get the remote process handle.
  inline HANDLE getProcess() const { return _hProcess; }
  //! @brief Get the virtual memory manager.
  inline VirtualMemoryManager* getVirtualMemoryManager() { return &_memoryManager; }

  // --------------------------------------------------------------------------
  // [Interface]
  // --------------------------------------------------------------------------
 
  virtual uint32_t generate(void** dest, Assembler* assembler);

  // --------------------------------------------------------------------------
  // [Members]
  // --------------------------------------------------------------------------

protected:
  //! @brief Process.
  HANDLE _hProcess;

  //! @brief Virtual memory manager.
  VirtualMemoryManager _memoryManager;
 
private:
  ASMJIT_DISABLE_COPY(RemoteCodeGenerator)
};

} // AsmJit namespace

// [Guard]
#endif // _ASMJIT_EXT_REMOTECODEGENERATOR_H