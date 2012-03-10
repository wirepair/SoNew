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

#ifndef PARSEDARGUMENT_H_
#define PARSEDARGUMENT_H_

#include <string>
#include <vector>
#include <map>

namespace cppargparser {

class ParsedArgument {
public:
    /**
     * Puts the argument and argument value.
     * @param arg the argument
     * @param value the argument value
     */
    void putArgument(const std::string& arg, const std::string& value);

    /**
     * Gets the argument value.
     * @param arg the argument
     * @return the argument value
     */
    std::string getValue(const std::string& arg) const;

    /**
     * Gets the argument values.
     * @param arg the argument
     * @return the argument values
     */
    std::vector<std::string> getValues(const std::string& arg) const;

    /**
     * Checks if the given arg was called.
     * @return true if a given arg was called; false otherwise
     */
    bool hasArgument(const std::string& arg) const;

    virtual ~ParsedArgument();

private:
    std::map<std::string, std::vector<std::string> > args;
};

} /* namespace cppargparser */
#endif /* PARSEDARGUMENT_H_ */
