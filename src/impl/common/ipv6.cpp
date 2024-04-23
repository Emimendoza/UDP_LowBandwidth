#include "ipv6.h"
#include "string_manip.h"
#include <stdexcept>
#include <cstring>

using namespace udp_low_bandwidth;

ipv6_address::ipv6_address(const std::string& str) : address(16) {
	auto parts = string_manip::split(str, ":");
	if (parts.size() != 8) {
		throw std::invalid_argument("Invalid IPv6 address");
	}
	for (int i = 0; i < 8; i++) {
		int octet;

		if (parts[i].empty()) {
			octet = 0;
		} else {
			octet = std::stoi(parts[i], nullptr, 16);
		}

		if (octet < 0 || octet > 0xFFFF) {
			throw std::invalid_argument("Invalid IPv6 address");
		}
		data[i * 2] = (std::byte)(octet >> 8);
		data[i * 2 + 1] = (std::byte)(octet & 0xFF);
	}
}

std::string ipv6_address::to_string() const {
	std::string result;
	for (int i = 0; i < 8; i++) {
		result += string_manip::to_hex(data[i * 2]);
		result += string_manip::to_hex(data[i * 2 + 1]);
		if (i < 7) {
			result += ":";
		}
	}
	return result;
}

ipv6_address::ipv6_address(const bytes& addr) : address(addr) {
	if (addr.get_size() != 16) {
		throw std::invalid_argument("Invalid IPv6 address");
	}
}