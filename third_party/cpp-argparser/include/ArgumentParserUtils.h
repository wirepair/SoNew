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

#ifndef ARGUMENTPARSERUTILS_H_
#define ARGUMENTPARSERUTILS_H_

#include <string>
#include <vector>
#include <sstream>

namespace cppargparser {

bool isShortArg(const std::string& s) {
    if (s.size() > 1) {
        if (s[0] == '-') {
            return true;
        }
    }
    return false;
}

bool isLongArg(const std::string& s) {
    if (s.size() > 2) {
        if (s.substr(0, 2) == "--") {
            return true;
        }
    }
    return false;
}

std::string toString(const std::vector<std::string>& v) {
    using namespace std;
    string s = "[";
    for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i) {
        s += *i + ", ";
    }
    s = s.substr(0, s.size()-2);
    s += "]";

    return s;
}

std::string toString(int i) {
    using namespace std;
    stringstream ss;
    ss << i;
    return ss.str();
}

} /* namespace cppargparser */
#endif /* ARGUMENTPARSERUTILS_H_ */
