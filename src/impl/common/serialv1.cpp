#include "serial.h"
#include <stdexcept>
#include <cmath>
#include "magic.h"

// All data is in big endian format (aka higher -> lower memory addresses)

using namespace udp_low_bandwidth::magic::serial::v1;

namespace udp_low_bandwidth::serial::v1 {
	// Unsigned integers
	bytes serialize(const bool& data){
		bytes result(1);
		result[0] = data ? (std::byte)1 : (std::byte)0;
		return result;
	}

	bytes serialize(const uint8_t& data){
		bytes result(1);
		result[0] = (std::byte)data;
		return result;
	}

	bytes serialize(const uint16_t& data){
		bytes result(2);
		
		result[0] = (std::byte)(data >> 8);
		result[1] = (std::byte)data;
		return result;
	}

	bytes serialize(const uint32_t& data){
		bytes result(4);
		
		result[0] = (std::byte)(data >> 24);
		result[1] = (std::byte)(data >> 16);
		result[2] = (std::byte)(data >> 8);
		result[3] = (std::byte)data;
		return result;
	}

	bytes serialize(const uint64_t& data){
		bytes result(8);
		
		result[0] = (std::byte)(data >> 56);
		result[1] = (std::byte)(data >> 48);
		result[2] = (std::byte)(data >> 40);
		result[3] = (std::byte)(data >> 32);
		result[4] = (std::byte)(data >> 24);
		result[5] = (std::byte)(data >> 16);
		result[6] = (std::byte)(data >> 8);
		result[7] = (std::byte)data;
		return result;
	}

	// Signed integers
	bytes serialize(const int8_t& data){
		bytes result(1);
		
		result[0] = (std::byte)data;
		return result;
	}

	bytes serialize(const int16_t& data){
		bytes result(2);
		
		result[0] = (std::byte)(data >> 8);
		result[1] = (std::byte)data;
		return result;
	}

	bytes serialize(const int32_t& data){
		bytes result(4);
		
		result[0] = (std::byte)(data >> 24);
		result[1] = (std::byte)(data >> 16);
		result[2] = (std::byte)(data >> 8);
		result[3] = (std::byte)data;
		return result;
	}

	bytes serialize(const int64_t& data){
		bytes result(8);
		
		result[0] = (std::byte)(data >> 56);
		result[1] = (std::byte)(data >> 48);
		result[2] = (std::byte)(data >> 40);
		result[3] = (std::byte)(data >> 32);
		result[4] = (std::byte)(data >> 24);
		result[5] = (std::byte)(data >> 16);
		result[6] = (std::byte)(data >> 8);
		result[7] = (std::byte)data;
		return result;
	}

	// Floating point
	// We need to deconstruct the float into its components
	// This is because we can't just cast the float to a byte array

	struct float_components {
		uint32_t mantissa;
		uint8_t exponent;
		bool sign;
	};

	bytes serialize(const float& data){
		float_components components{};
		components.sign = std::signbit(data);
		float abs_data = std::abs(data);
		int exponent = 0;
		float mantissa = std::frexp(abs_data, &exponent);
		components.exponent = exponent + 127;
		components.mantissa = (uint32_t)(mantissa * (1 << 23));

		std::vector<bytes> parts = {
			serialize(components.sign),
			serialize(components.exponent),
			serialize(components.mantissa)
		};
		return bytes(parts);
	}

	// Similar thing for doubles
	struct double_components {
		uint64_t mantissa;
		uint16_t exponent;
		bool sign;
	};

	bytes serialize(const double& data){
		double_components components{};
		components.sign = std::signbit(data);
		double abs_data = std::abs(data);
		int exponent = 0;
		double mantissa = std::frexp(abs_data, &exponent);
		components.exponent = exponent + 1023;
		components.mantissa = (uint64_t)(mantissa * (1ULL << 52));

		std::vector<bytes> parts = {
			serialize(components.sign),
			serialize(components.exponent),
			serialize(components.mantissa)
		};
		return bytes(parts);
	}

	// Deserialization

	// Unsigned integers
	bool deserialize_bool(const bytes& data){
		if (data.get_size() != 1) throw std::length_error("Invalid data size");
		return data[0] == (std::byte)1;
	}

	uint8_t deserialize_uint8(const bytes& data){
		if (data.get_size() != 1) throw std::length_error("Invalid data size");
		return (uint8_t)data[0];
	}

	uint16_t deserialize_uint16(const bytes& data){
		if (data.get_size() != 2) throw std::length_error("Invalid data size");
		return (uint16_t)(
				data[0] << 8 |
				data[1]);
	}

	uint32_t deserialize_uint32(const bytes& data){
		if (data.get_size() != 4) throw std::length_error("Invalid data size");
		return (uint32_t)(
				data[0] << 24 |
				data[1] << 16 |
				data[2] << 8 |
				data[3]);
	}

	uint64_t deserialize_uint64(const bytes& data){
		if (data.get_size() != 8) throw std::length_error("Invalid data size");
		return (uint64_t)(
				data[0] << 56 |
				data[1] << 48 |
				data[2] << 40 |
				data[3] << 32 |
				data[4] << 24 |
				data[5] << 16 |
				data[6] << 8 |
				data[7]);
	}

	// Signed integers

	int8_t deserialize_int8(const bytes& data){
		if (data.get_size() != 1) throw std::length_error("Invalid data size");
		return (int8_t)data[0];
	}

	int16_t deserialize_int16(const bytes& data){
		if (data.get_size() != 2) throw std::length_error("Invalid data size");
		return (int16_t)(
				data[0] << 8 |
				data[1]);
	}

	int32_t deserialize_int32(const bytes& data){
		if (data.get_size() != 4) throw std::length_error("Invalid data size");
		return (int32_t)(
				data[0] << 24 |
				data[1] << 16 |
				data[2] << 8 |
				data[3]);
	}

	int64_t deserialize_int64(const bytes& data){
		if (data.get_size() != 8) throw std::length_error("Invalid data size");
		return (int64_t)(
				data[0] << 56 |
				data[1] << 48 |
				data[2] << 40 |
				data[3] << 32 |
				data[4] << 24 |
				data[5] << 16 |
				data[6] << 8 |
				data[7]);
	}

	// Floating point

	// This is essentially reconstructing the float from its components

	float deserialize_float(const bytes& data){
		if (data.get_size() != FLOAT_SERIALIZED_SIZE) throw std::length_error("Invalid data size");
		bool sign = deserialize_bool(data.slice(0, 1));
		uint8_t exponent = deserialize_uint8(data.slice(1, 2));
		uint32_t mantissa = deserialize_uint32(data.slice(2, 6));
		float result = (float)mantissa / (1 << 23);
		result = std::ldexp(result, exponent - 127);
		if (sign) result = -result;
		return result;
	}

	double deserialize_double(const bytes& data){
		if (data.get_size() != DOUBLE_SERIALIZED_SIZE) throw std::length_error("Invalid data size");
		bool sign = deserialize_bool(data.slice(0, 1));
		uint16_t exponent = deserialize_uint16(data.slice(1, 3));
		uint64_t mantissa = deserialize_uint64(data.slice(3, 11));
		double result = (double)mantissa / (1ULL << 52);
		result = std::ldexp(result, exponent - 1023);
		if (sign) result = -result;
		return result;
	}
}
