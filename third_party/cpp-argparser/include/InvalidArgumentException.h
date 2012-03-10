// Copyright 2012, Fredy Wijaya
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the Lesser GNU General Public License as published by
// the Free Software Foundation, either version 3.0 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// Lesser GNU General Public License for more details.
//
// You should have received a copy of the Lesser GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>

#ifndef INVALIDARGUMENTEXCEPTION_H_
#define INVALIDARGUMENTEXCEPTION_H_

#include <string>
#include <exception>

namespace cppargparser {

class InvalidArgumentException : public std::exception {
public:
    InvalidArgumentException(const std::string& _message) : message(_message) {}

    virtual const char* what() const throw() {
        return message.c_str();
    }

    virtual ~InvalidArgumentException() throw() {}

private:
    std::string message;
};

} /* namespace cppargparser */
#endif /* INVALIDARGUMENTEXCEPTION_H_ */
