#ifndef UDP_LowBandwidth_IP_4_EXPORTS
#define UDP_LowBandwidth_IP_4_EXPORTS
#include "ip_base.h"
namespace udp_low_bandwidth{
	class ipv4_address : public address{
	public:
		explicit ipv4_address(const std::string &str);
		explicit ipv4_address(const bytes& addr);

		[[nodiscard]] address_type get_type() const override{
			return address_type::ipv4;
		}
		[[nodiscard]] std::string to_string() const override;
	};
}

#endif