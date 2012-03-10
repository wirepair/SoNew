#include "sonewargumentvalidator.h"

namespace SoNew {
	bool UIntTypeValidator::validate(const vector<string>& values) {
		for (vector<string>::const_iterator i = values.begin(); i != values.end(); ++i) {
            istringstream iss(*i);
            unsigned int injectiontype;
            try {
                iss >> injectiontype;
				if (injectiontype < this->minimum || injectiontype > this->maximum) {
                    return false;
                }
            } catch (...) {
                return false;
            }
        }
        return true;
    }

	bool FilePathValidator::validate(const vector<string>& values) {
		for (vector<string>::const_iterator i = values.begin(); i != values.end(); ++i) {
            try {
				// see if we even have a valid file to work with.
				istringstream iss(*i);
				ifstream ifile(iss.str().c_str());
				if(ifile.fail())
					return false;
				return true;
            } catch (...) {
                return false;
            }
        }
        return false;
    }
}