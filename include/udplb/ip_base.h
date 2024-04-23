#ifndef UDP_LowBandwidth_IP_EXPORTS
#define UDP_LowBandwidth_IP_EXPORTS
#include <string>
#include <array>
#include <bytes.h>

namespace udp_low_bandwidth{
	enum class address_type{
		ipv4,
		ipv6
	};

	class address{
	protected:
		explicit address(uint64_t size) : data(size) {}
		explicit address(const bytes& data) : data(bytes(data)) {}
	public:
		const bytes data;

		/**
		 * @brief Returns the type of the address
		 * @return The type of the address
		 */

		[[nodiscard]] virtual address_type get_type() const = 0;

		/**
		 * @brief Returns the address as a string
		 * @return The address as a string
		 */
		[[nodiscard]] virtual std::string to_string() const = 0;
	};
}

#endif