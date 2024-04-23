#ifndef UDP_LowBandwidth_SERIAL_EXPORTS
#define UDP_LowBandwidth_SERIAL_EXPORTS
#include "bytes.h"

/**
 * @brief Namespace for the UDP Low Bandwidth library Serial module
 *
 * This namespace contains two functions, one for serializing data and one for deserializing data.
 * Each function has overloads for each c++ int/double/bool type. It converts between the type and the bytes struct.
 * All numbers are stored in big endian format.
 */
namespace udp_low_bandwidth::serial {

	/**
	 * @brief Namespace for the first version of the UDP Low Bandwidth library Serial module
	 */
	namespace v1 {
		bytes serialize(const bool &data);
		bytes serialize(const int8_t &data);
		bytes serialize(const int16_t &data);
		bytes serialize(const int32_t &data);
		bytes serialize(const int64_t &data);
		bytes serialize(const uint8_t &data);
		bytes serialize(const uint16_t &data);
		bytes serialize(const uint32_t &data);
		bytes serialize(const uint64_t &data);
		bytes serialize(const float &data);
		bytes serialize(const double &data);


		bool deserialize_bool(const bytes &data);
		int8_t deserialize_int8(const bytes &data);
		int16_t deserialize_int16(const bytes &data);
		int32_t deserialize_int32(const bytes &data);
		int64_t deserialize_int64(const bytes &data);
		uint8_t deserialize_uint8(const bytes &data);
		uint16_t deserialize_uint16(const bytes &data);
		uint32_t deserialize_uint32(const bytes &data);
		uint64_t deserialize_uint64(const bytes &data);
		float deserialize_float(const bytes &data);
		double deserialize_double(const bytes &data);
	}
}

#endif