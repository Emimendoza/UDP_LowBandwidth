#include <udplb/ipv4.h>
#include <cassert>
#include <stdexcept>

using namespace udp_low_bandwidth;

int main() {
	try {
		address *addr = new ipv4_address(0, "0.0.0.0.0");
		delete addr;
	} catch (std::invalid_argument& e) {
		return 1;
	}
	// The test should fail here
	return 0;
}