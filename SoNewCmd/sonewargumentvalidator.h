#ifndef SONEWARGUMENTVALIDATOR_H
#define SONEWARGUMENTVALIDATOR_H

#include "utils.h"
#include "Validator.h"
#include <fstream>


namespace SoNew {
	class UIntTypeValidator : public cppargparser::Validator {
	public:
		UIntTypeValidator() : minimum(0), maximum(65536) {};
		UIntTypeValidator(const unsigned int new_min, const unsigned int new_max) : minimum(new_min), maximum(new_max) {};
		bool validate(const vector<string>& values);
		~UIntTypeValidator() {}
	private:
		unsigned int minimum;
		unsigned int maximum;
	};

	class FilePathValidator : public cppargparser::Validator {
	public:
		bool validate(const vector<string>& values);
		~FilePathValidator() {}
	};
}
#endif