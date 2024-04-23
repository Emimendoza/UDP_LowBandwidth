#include "string_manip.h"

using namespace udp_low_bandwidth;

std::vector<std::string> string_manip::split(const std::string& str, const std::string& delimiter) {
	std::vector<std::string> result;
	size_t start = 0;
	size_t end = str.find(delimiter);
	while (end != std::string::npos) {
		result.push_back(str.substr(start, end - start));
		start = end + delimiter.size();
		end = str.find(delimiter, start);
	}
	result.push_back(str.substr(start, end));
	return result;
}

std::string string_manip::to_hex(const std::byte& b) {
	char result[3];
	sprintf(result, "%02X", (unsigned char)b);
	return result;
}

std::string string_manip::to_dec(const std::byte& b) {
	char result[4];
	sprintf(result, "%d", (unsigned char)b);
	return result;
}