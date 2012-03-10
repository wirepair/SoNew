#include "Method.h"

namespace SoNew {
	// TODO: Implement
	
	Method::Method(const cppargparser::ParsedArgument& parsedArguments) {
		m_pFunctionName = m_pDllName = 0;
		if (parsedArguments.hasArgument("-d"))
			m_pDllName = new String(StringToWstring(parsedArguments.getValue("-d")));
		if (parsedArguments.hasArgument("-f"))
			m_pFunctionName = new String(StringToWstring(parsedArguments.getValue("-f")));
		int inj_type = StringToNumber<int>(parsedArguments.getValue("-i"));
		m_injectionType = static_cast<InjectionType>(inj_type);
	}

	Method::Method(const String& dllname) {
		m_pFunctionName = 0;
		m_pDllName = new String(dllname);
	}
	
	Method::Method(const String& dllname, const String& function_name) {
		m_pDllName = m_pFunctionName = 0;
		m_pDllName = new String(dllname);
		m_pFunctionName = new String(function_name);
	}
	
	Method& Method::operator=(const Method &rhs) { // assignment op
		if (this != &rhs) {
			delete m_pDllName;
			delete m_pFunctionName;
			m_pDllName = m_pFunctionName = 0;
			if (rhs.m_pDllName != 0)
				m_pDllName = new String(*rhs.m_pDllName);
			if (rhs.m_pFunctionName != 0)
				m_pFunctionName = new String(*rhs.m_pFunctionName);
			m_injectionType = rhs.m_injectionType;
		}
		return *this;
	}

	Method::Method(const Method &rhs) {  // copy constructor
		m_pDllName = m_pFunctionName = 0;
		if (rhs.m_pDllName != 0)
			m_pDllName = new String(*rhs.m_pDllName);
		if (rhs.m_pFunctionName != 0)
			m_pFunctionName = new String(*rhs.m_pFunctionName);
		m_injectionType = rhs.m_injectionType;
	}

	Method::~Method() {
		delete m_pDllName;
		delete m_pFunctionName;
	}
}