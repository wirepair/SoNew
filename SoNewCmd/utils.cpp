#include "utils.h"

using namespace cppargparser;

namespace SoNew {

	void ShowUsage(const SoNewArgumentParser &argParser) {
		argParser.showHelp("SoNew [options]", 20);
	}

	void ShowError(const SoNewArgumentParser &argParser, const String &message) {
		ShowUsage(argParser);
		tcout << message << endl;
		exit(-1);

	}

	bool SetArguments(SoNewArgumentParser *argumentParser, UIntTypeValidator *injection_validator, 
		UIntTypeValidator *pid_validator, FilePathValidator *filepath_validator) 
	{
		std::string injection_msg = "An injection type (Choose by #):\n\
	\t\t\t1. CreateRemoteThread & LoadLibrary\n\
	\t\t\t2. CreateRemoteThread & WriteMemoryProcess\n\
	\t\t\t3. CodeCave (NOT IMPLEMENTED)\n\
	\t\t\t4. IATHooks (NOT IMPLEMENTED)";
		argumentParser->addArgument(Argument("-h", "--h", "Prints this help", 0, false));
		argumentParser->addArgument(Argument("-i", 
			"--injection", injection_msg, 1, false , injection_validator));
		argumentParser->addArgument(Argument("-v", "--verbose", "Be verbose", 0, false));
		argumentParser->addArgument(Argument("-l", "--listprocs", 
			"Lists the processes and their pid", 0, false));
		argumentParser->addArgument(Argument("-p", "--pid", 
			"<pid> Select a process by pid to inject into.", 1, false, pid_validator));
		argumentParser->addArgument(Argument("-n", "--procname", "<procname> Select process by name", 1, false));
		argumentParser->addArgument(Argument("-d", "--dll", 
			"<dllpath> Full path to dll to inject", 1, false, filepath_validator));
		argumentParser->addArgument(Argument("-f", "--funcname",
			"<dll func name> Function name in dll to call (if needed)", 1, false));
		return true;
	}

	ParsedArgument ValidateArguments(SoNewArgumentParser &argParser, int argc, char **argv) {
		
		UIntTypeValidator *inj_validator = new UIntTypeValidator(1, 4);
		UIntTypeValidator *pid_validator = new UIntTypeValidator();
		FilePathValidator *fp_validator = new FilePathValidator();
		SetArguments(&argParser, inj_validator, pid_validator, fp_validator);
		ParsedArgument pa;
		try {
			pa = argParser.parse(argc, argv);
			// check if we're just listing processes first.
			if (pa.hasArgument("-l")) {
				PrintProcessList();
				exit(0);
			}
			if (pa.hasArgument("-h")) {
				ShowUsage(argParser);
				exit(0);
			}
			if (!pa.hasArgument("-p") && !pa.hasArgument("-n"))
				ShowError(argParser, L"Error: We require a process name or pid!");
			if (!pa.hasArgument("-i"))
				ShowError(argParser, L"Error: We require an injection method!");
		} catch(InvalidArgumentException iae) {
			String message = StringToWstring(iae.what());
			ShowError(argParser, message);
		}
		delete inj_validator;
		delete pid_validator;
		delete fp_validator;
		return pa;
	}

	// NFI if this is the best way to convert wchar's to chars...
	char* narrow( const wstring& strText) {
		ostringstream stm;
		const ctype<char> &ctfacet = use_facet< ctype<char> >( stm.getloc() ) ;
		for( size_t i=0 ; i<strText.size() ; ++i )
			stm << ctfacet.narrow( strText[i], 0 ) ;
		string newstr = stm.str();
		size_t len = newstr.size()+1;
		char* c = new char [len];
		strcpy_s(c, len, newstr.c_str());
		return c;

	}
	String StringToWstring(const string& input) {
		return String(input.begin(), input.end());
	}
}