#ifndef ApplicationArgument_H
#define ApplicationArgument_H
#include "utils.h"
#include <assert.h>

// Class Layout / Ideas clearly taken from QT
namespace Arguments {
	enum ArgumentType {
		ArgumentInt = 0,
		ArgumentFloat = 1,
		ArgumentDouble = 2,
		ArgumentString = 3
	};

	//typedef list<string> StringList; 

	class ArgumentPrivate;

	class ApplicationArgument {
	public:
		ApplicationArgument();
		ApplicationArgument(const ApplicationArgument &rhs);
		ApplicationArgument(const String &name, const String &description, ArgumentType argtype);
		~ApplicationArgument();
		ApplicationArgument &operator=(const ApplicationArgument &rhs);
		bool operator==(const ApplicationArgument &rhs) const;

		void setName(const String &newName);
		String name() const;
		void setDescription(const String &newDescription);
		String description() const;

		ArgumentType type() const;
		void setType(ArgumentType newType);

		void setMinimumOccurrence(int minimum);
		int minimumOccurrence() const;
		void setMaximumOccurrence(int maximum);
		int maximumOccurrence() const;
	protected:
		ArgumentPrivate* m_pArgument;
	};

}
#endif