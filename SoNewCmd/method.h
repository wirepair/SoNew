#ifndef METHOD_H
#define METHOD_H

#include "utils.h"
#include "ParsedArgument.h"
using cppargparser::Argument;

namespace SoNew {

	enum InjectionType {
		CRTLL = 1,
		CRTWMP = 2,
		CodeCave = 3,
		IATHooks = 4
	};

	struct Method {
		Method() : m_pDllName(0), m_pFunctionName(0), m_injectionType(CRTLL) {};
		Method(const cppargparser::ParsedArgument& parsedArguments);
		Method(const String& dllname);
		Method(const String& dllname, const String& function_name);
		Method &operator=(const Method& rhs); // assignment op		
		Method(const Method& rhs); // copy constructor
		~Method();
	
		InjectionType m_injectionType;
		String* m_pDllName;
		String* m_pFunctionName;
	};
}
#endif
