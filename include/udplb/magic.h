#ifndef UDP_LowBandwidth_MAGIC_EXPORTS
#define UDP_LowBandwidth_MAGIC_EXPORTS
#include <cinttypes>

/**
 * @brief A namespace for magic numbers
 */
namespace udp_low_bandwidth::magic{

	/**
	 * @brief The magic number for the UDP Low Bandwidth protocol start packet
	 *
	 * @details The magic number is used to identify the start of a UDP Low Bandwidth packet
	 * @note The magic number is 8 bytes long
	 * @note The magic number is {0xF7, 'u','D','p','l','B',0x1B,0xFB}
	 *
	 * This number was chosen as a mix of invalid utf-8 characters (0xF7, 0xFB), string characters
	 * ('u','D','p','l','B'), and an ascii escape character (0x1B), thus this is unlikely to be found in a normal
	 * data stream, and won't be confused with other protocols/plaintext data.
	 */
	const uint8_t HEADER_MAGIC[] = {0xF7, 'u','D','p','l','B',0x1B,0xFB};
}

namespace udp_low_bandwidth::magic::bytes{
	const uint64_t MAX_SIZE = UINT64_MAX;
}

namespace udp_low_bandwidth::magic::serial::v1{
	/**
	 * @brief The size of a serialized float in serial_protocol_v1
	 * @note 4 (mantissa) + 1 (exponent) + 1 (sign)
	 */
	const uint16_t FLOAT_SERIALIZED_SIZE = 6;
	/**
	 * @brief The size of a serialized double in serial_protocol_v1
	 * @note 8 (mantissa) + 1 (exponent) + 1 (sign)
	 */
	const uint16_t DOUBLE_SERIALIZED_SIZE = 11;
}

#endif
