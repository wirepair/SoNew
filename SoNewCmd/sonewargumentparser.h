#ifndef SONEWARGUMENTPARSER_H
#define SONEWARGUMENTPARSER_H
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "Argument.h"
#include "ArgumentParser.h"
#include "ParsedArgument.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using cppargparser::Argument;

namespace SoNew {

	class SoNewArgumentParser: public cppargparser::ArgumentParser {
	public:
		void showHelp(const std::string& programName, const int spacing) const;
	};
}
#endif