#ifndef UDP_LowBandwidth_COMMON_EXPORTS
#define UDP_LowBandwidth_COMMON_EXPORTS
#include "ipv6.h"
#include "ipv4.h"

namespace udp_low_bandwidth{
	typedef unsigned short port;

	const unsigned short MAX_PACKET_SIZE = 512;
	const unsigned short MAX_DATA_SIZE = MAX_PACKET_SIZE - 3;

}




#endif
