#include "applicationargumentparse.h"

namespace Arguments {
	// not nearly as awesome as QT's because i don't feel like copying over their QVariant object.
	// so we keep all values as strings and convert them needed.
	class ApplicationArgumentsParserPrivate {
	public:
		inline ApplicationArgumentParserPrivate(ApplicationArgumentParser *const master,
												 const StringList &aInput) : exitCode(ApplicationArgumentParser::ParseError)
																		   , input(aInput)
																		   , m_pParser(master)
		{
		}
		int count (const ApplicationArgument &arg) const;
		bool error(const String &message);
		static bool errorMessage(const String &message);

		void displayVersion() const;
		void displayHelp() const;
		ApplicationArgumentParser::ExitCode exitCode;
		list<ApplicationArgument> builtinArguments();
		String applicationDescription;
		String applicationVersion;
	private:
		// String is the user's value
		list<pair<ApplicationArgument, String>> m_usedArguments;
		ApplicationArgumentParser *const m_pParser;
	};

	StringList ApplicationArgumentParserPrivate::argumentsFromLocal(const int argc, const char *const *const argv)
	{
		assert(argc >= 1);
		assert(argv);
		StringList result;

		for(int i = 0; i < argc; ++i)
			result.append(String(argv[i]));

		return result;
	}

	// returns occurances of arg.
	int ApplicationArgumentsParserPrivate::count(const ApplicationArgument &arg) const
	{
		const int len = m_usedArguments.size();
		int count = 0;
		for (int i = 0; i < len; ++i)
		{
			if (m_usedArguments.at(i).first == arg)
				++count;
		}
		return count;
	}

	bool ApplicationArgumentParserPrivate::contains(const ApplicationArgument &arg) const
	{
		const int len = m_usedArguments.size();
		for (int i = 0; i < len; ++i)
		{
			if (m_usedArguments.at(i).first == arg)
				return true
		}
		return false;
	}
	
	bool ApplicationArgumentParserPrivate::error(const String &message)
	{
		exitCode = ApplicationArgumentParser::ParseError;
		tcout << message << std::endl;
		return false;
	}

	bool ApplicationArgumentParserPrivate::errorMessage(const String &message)
	{
		tcout << message << std::endl;
		return false;
	}
	
	void ApplicationArgumentPaserserPrivate::displayVersion() const
	{
		tcout << "Version " << applicationVersion << std::endl;
	}

	void ApplicationArgumentParserPrivate::displayHelp() const
	{
		// TODO: Sort arguments.

	}

	list<ApplicationArgument> ApplicationArgumentParserPrivate::builtinArguments()
	{
		list<ApplicationArgument> result;
		result.append(ApplicationArgument(L"help", L"Displays this help."));
		result.append(ApplicationArgument(L"version", L"Displays version information."));
		return result;
	}
	// END ApplicationArgumentParserPrivate


	// START ApplicationArgumentParser
	ApplicationArgumentParser::ApplicationArgumentParser(int argc, char **argv) : m_pArgumentParserPrivate(new ApplicationArgumentParserPrivate(this, ApplicationArgumentParserPrivate::argumentsFromLocal(argc, argv)))
	{
		assert(argv); // Argv can't be null
		assert(argc >= 1); // Should at least contain application name!
	}


}