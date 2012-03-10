#ifndef APPARGPARSE_H
#define APPARGPARSE_H
#include <list>
#include <utility>
#include "applicationargument.h"

namespace Arguments {
	class ApplicationArgumentParserPrivate;
	typedef StringList list<string>;

	class ApplicationArgumentParser {
	public:
		ApplicationArgumentParser(int argc, char **argv);
		ApplicationArgumentParser(const list &input);
		virtual ~ApplicationArgumentParser();
		void addArgument(const ApplicationArgument &argument);
		void setDeclaredArguments(const list<ApplicationArgument> &arguments);
		list<ApplicationArgument> declaredArguments() const;


		int count(const ApplicationArgument &argument) const;
		bool has(const ApplicationArgument &argument) const;

		virtual bool parse();
		ExitCode exitCode() const;
		//QVariant value(const ApplicationArgument &argument) const;
		//QVariantList values(const ApplicationArgument &argument) const;
		void setApplicationDescription(const String &description);
		void setApplicationVersion(const String &version);
		virtual void message(const String &message) const;

	protected:
		void setExitCode(ExitCode code);

	private:
		friend class ApplicationArgumentParserPrivate;
		ApplicationArgumentParserPrivate *m_pArgumentParserPrivate;
	};
}
#endif