#include "ApplicationArgument.h"

namespace Arguments {
	// holds our argument data
	class ArgumentPrivate {
	public:
		inline ArgumentPrivate(const String& argname, 
						  const String& argdesc, 
						  const ArgumentType argtype) : name(argname)
											 , description(argdesc)
											 , type(argtype)
											 , minimum(0)
											 , maximum(1)
		{
		}
		
		String name;
		String description;
		ArgumentType type;
		int minimum;
		int maximum;
		bool isNameless;
	};

	ApplicationArgument::ApplicationArgument() : m_pArgument(new ArgumentPrivate(String(), String(), ArgumentString))
	{
	}
	
	ApplicationArgument::ApplicationArgument(const ApplicationArgument& rhs) : m_pArgument(new ArgumentPrivate(*rhs.m_pArgument))
	{
	}

	ApplicationArgument::~ApplicationArgument()
	{
		delete m_pArgument;
	}

	ApplicationArgument::ApplicationArgument(const String &name, const String &description, ArgumentType argtype) : m_pArgument(new ArgumentPrivate(name, description, argtype))
	{
	}

	ApplicationArgument &ApplicationArgument::operator=(const ApplicationArgument &rhs) 
	{
		if (this != &rhs)
			*m_pArgument = *rhs.m_pArgument;

		return *this;
	}

	// compares argument names
	bool ApplicationArgument::operator==(const ApplicationArgument &rhs) const
	{
		return name() == rhs.name();
	}

	// sets the name
	void ApplicationArgument::setName(const String &newName) 
	{
		m_pArgument->name = newName;
	}
	
	String ApplicationArgument::name() const {
		return m_pArgument->name;
	}

	// sets the type
	void ApplicationArgument::setType(ArgumentType newType)
	{
		m_pArgument->type = newType;
	}

	// returns the type
	ArgumentType ApplicationArgument::type() const {
		return m_pArgument->type;
	}

	void ApplicationArgument::setMinimumOccurrence(int minimum)
	{
		m_pArgument->minimum = minimum;
	}

	int ApplicationArgument::minimumOccurrence() const
	{
		return m_pArgument->minimum;
	}

	void ApplicationArgument::setMaximumOccurrence(int maximum)
	{
		assert(maximum == -1 || maximum >= 1);
		m_pArgument->maximum = maximum;
	}

	int ApplicationArgument::maximumOccurrence() const
	{
		return m_pArgument->maximum;
	}
	
	void ApplicationArgument::setDescription(const String &newDescription)
	{
		m_pArgument->description = newDescription;
	}
	
	String ApplicationArgument::description() const
	{
		return m_pArgument->description;
	}

}