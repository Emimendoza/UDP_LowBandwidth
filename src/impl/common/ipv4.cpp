#include <stdexcept>
#include <cstring>
#include "ipv4.h"
#include "string_manip.h"
using namespace udp_low_bandwidth;

ipv4_address::ipv4_address(const std::string &str) : address(4) {
	auto parts = string_manip::split(str, ".");
	if (parts.size() != 4) {
		throw std::invalid_argument("Invalid IPv4 address");
	}
	for (int i = 0; i < 4; i++) {
		int octet = std::stoi(parts[i]);
		if (octet < 0 || octet > 255) {
			throw std::invalid_argument("Invalid IPv4 address");
		}
		data[i] = (std::byte)octet;
	}
}

std::string ipv4_address::to_string() const {
	std::string result;
	for (int i = 0; i < 4; i++) {
		result += string_manip::to_dec(data[i]);
		if (i < 3) {
			result += ".";
		}
	}
	return result;
}

ipv4_address::ipv4_address(const bytes &addr) : address(addr) {
	if (addr.get_size() != 4) {
		throw std::invalid_argument("Invalid IPv4 address");
	}
}
