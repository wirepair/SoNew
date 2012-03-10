#include "sonewargumentparser.h"

namespace SoNew {
	void SoNewArgumentParser::showHelp(const std::string& programName, const int spacing) const {
		cout << programName << endl;
		cout << "Options:" << endl;
		for (vector<Argument>::const_iterator i = vargs.begin(); i != vargs.end(); ++i) {
			string options = "";
			if (i->isShortArg()) {
				options += i->getShortArg();
				if (i->isLongArg()) {
					options += ", ";
				}
			}
			if (i->isLongArg()) {
				options += i->getLongArg();
			}
			cout << string(4, ' ') << options << string(spacing-options.size(), ' ') <<
				i->getDescription() << endl;
		}
	}
}