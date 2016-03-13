/*
 * misc.C
 *
 *  Created on: Mar 11, 2016
 *      Author: mrilee
 */

#include <misc.h>

std::string executableName(const char* arg0) {
	std::string path = std::string(arg0);
	std::vector<std::string> pathList;
	std::regex pat { R"(/)" };
	std::sregex_token_iterator iter(path.begin(),path.end(),pat,-1);
	std::sregex_token_iterator end;
	for( ; iter != end; ++iter ) {
		// std::cout << *iter << std::endl;
		pathList.push_back(*iter);
	}
	return pathList.back();
}

