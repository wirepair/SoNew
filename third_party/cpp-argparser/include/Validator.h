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

#ifndef VALIDATOR_H_
#define VALIDATOR_H_

#include <string>
#include <vector>

namespace cppargparser {

class Validator {
public:
    /**
     * Validates the argument.
     * @param values the argument values
     */
    virtual bool validate(const std::vector<std::string>& values) = 0;

    virtual ~Validator() {}
};

}

#endif /* VALIDATOR_H_ */
