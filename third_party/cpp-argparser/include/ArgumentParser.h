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

#ifndef ARGUMENTPARSER_H_
#define ARGUMENTPARSER_H_

#include <map>
#include <vector>
#include <string>
#include "Argument.h"
#include "ParsedArgument.h"

namespace cppargparser {

class ArgumentParser {
public:
    /**
     * Adds an argument.
     * @param arg the argument
     */
    void addArgument(const Argument& arg);

    /**
     * Parses the arguments.
     * @param argc the number of argument, the number of argument should
     *             include the program name, in other words just pass
     *             whatever you get from the main(argc, argv)
     *             if the number of arguments isn't correct, expect a segmentation fault :)
     * @param argv the arguments
     * @return the parsed argument
     */
    ParsedArgument parse(int argc, char** argv);

    /**
     * Shows/prints a help menu.
     * @param programName the program name
     */
    virtual void showHelp(const std::string& programName) const;

    virtual ~ArgumentParser();

protected:
    std::map<std::string, Argument> args;
    std::vector<Argument> vargs;
};

} /* namespace cppargparser */
#endif /* ARGUMENTPARSER_H_ */
