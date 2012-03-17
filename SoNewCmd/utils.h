#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <windows.h>

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#define String std::wstring
#else
#define tcout std::cout
#define String string
#endif


#include "win32functions.h"
#include "sonewargumentparser.h"
#include "ParsedArgument.h"
#include "sonewargumentvalidator.h"
#include "InvalidArgumentException.h"

using namespace std;
using namespace cppargparser;

namespace SoNew {
	class UIntTypeValidator; // forward declare
	class FilePathValidator; // forward declare

	// usage and argument parsing
	void ShowUsage(const SoNewArgumentParser &argParser);

	void ShowError(const SoNewArgumentParser &argParser, const String &message);

	bool SetArguments(SoNewArgumentParser *argParser, UIntTypeValidator *injection_validator, UIntTypeValidator *pid_validator, FilePathValidator *filepath_validator);

	ParsedArgument ValidateArguments(SoNewArgumentParser &argParser, int argc, char **argv);

	// Misc String/Number Helper Functions
	char* narrow(String &str);
	String StringToWstring(const string &input);
	
	template <class T> T StringToNumber ( const string &Text ) {
		stringstream ss(Text);
		T result;
		return ss >> result ? result : -1;
	}
	
	template <class T> std::string ToString(const T &t)
	{
		 std::ostringstream stream;
		 stream << t;
		 return stream.str();
	}
}
#endif