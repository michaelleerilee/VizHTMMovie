/*
 * misc.C
 *
 *  Created on: Mar 11, 2016
 *      Author: mrilee
 */

#include <misc.h>
#include <iomanip>
#include <sstream>

#include <ctime>

std::string executableNameFromPathAsCString(const char* arg0) {
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

std::string formattedZeroPaddedInteger(int iOut, const int fieldWidth, const char padChar) {
	std::stringstream out;
	out << std::setfill(padChar);
	out << std::setw(fieldWidth);
	out << iOut;
	return out.str();
}

std::string formattedOutFileName(
		const std::string baseName,
		const std::string itemName,
		const std::string extension) {
	std::stringstream outFile;
	outFile << baseName << itemName << extension;
	return outFile.str();
}

std::string formattedDateTime(std::string format) {
	char buffer[80];
	std::time_t rawtime;
	std::time(&rawtime);
	std::tm* timeinfo = std::gmtime(&rawtime);
	std::strftime(buffer,80,format.c_str(),timeinfo);
	return std::string(buffer);
}
