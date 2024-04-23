#ifndef UDP_LowBandwidth_IP_6_EXPORTS
#define UDP_LowBandwidth_IP_6_EXPORTS
#include "ip_base.h"
namespace udp_low_bandwidth{
	class ipv6_address : public address{
	public:
		explicit ipv6_address(const std::string& str);
		explicit ipv6_address(const bytes& addr);

		[[nodiscard]] address_type get_type() const override{
			return address_type::ipv6;
		}
		[[nodiscard]] std::string to_string() const override;
	};
}
#endif