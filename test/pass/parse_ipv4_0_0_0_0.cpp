#include <udplb/ipv4.h>
#include <cassert>

using namespace udp_low_bandwidth;

int main() {
	address *addr = new ipv4_address(0, "0.0.0.0");
	assert(addr->get_bytes()[0] == (std::byte)0);
	assert(addr->get_bytes()[1] == (std::byte)0);
	assert(addr->get_bytes()[2] == (std::byte)0);
	assert(addr->get_bytes()[3] == (std::byte)0);
	assert(addr->to_string() == "0.0.0.0");
	assert(addr->get_type() == address_type::ipv4);
	delete addr;
}