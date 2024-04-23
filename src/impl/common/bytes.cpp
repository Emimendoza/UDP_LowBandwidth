#include <cstring>
#include "magic.h"
#include "bytes.h"

namespace udp_low_bandwidth{
	void bytes::append(const udp_low_bandwidth::bytes &src) {
		std::shared_ptr<std::byte> new_data(new std::byte[this->size + src.size], std::default_delete<std::byte[]>());
		std::memcpy(new_data.get(), this->get_data(), this->size);
		std::memcpy(new_data.get() + this->size, src.get_data(), src.size);
		this->data = new_data;
		this->size += src.size;
	}

	bytes::bytes(uint64_t size) {
		this->data = std::shared_ptr<std::byte>(new std::byte[size], std::default_delete<std::byte[]>());
		this->size = size;
	}

	bytes::bytes(const udp_low_bandwidth::bytes &src) {
		this->data = std::shared_ptr<std::byte>(new std::byte[src.size], std::default_delete<std::byte[]>());
		std::memcpy(this->get_data(), src.get_data(), src.size);
		this->size = src.size;
	}

	bytes::bytes(const std::byte *data, uint64_t size) {
		this->data = std::shared_ptr<std::byte>(new std::byte[size], std::default_delete<std::byte[]>());
		std::memcpy(this->get_data(), data, size);
		this->size = size;
	}

	bytes::bytes(const uint8_t *data, uint64_t size) {
		this->data = std::shared_ptr<std::byte>(new std::byte[size], std::default_delete<std::byte[]>());
		std::memcpy(this->get_data(), data, size);
		this->size = size;
	}

	bytes::bytes(const std::vector<udp_low_bandwidth::bytes> &data) {
		uint64_t tmp_prev = 0;
		for (const auto &b : data) {
			this->size += b.size;
			if (this->size < tmp_prev) // Overflow
				throw std::length_error("The size of the bytes object is too large");
			tmp_prev = this->size;
		}
		this->data = std::shared_ptr<std::byte>(new std::byte[this->size], std::default_delete<std::byte[]>());
		uint64_t tmp_o = 0;
		for (const auto &b : data) {
			std::memcpy(this->get_data() + tmp_o, b.get_data(), b.size);
			tmp_o += b.size;
		}
	}

	bool bytes::operator==(const udp_low_bandwidth::bytes &other) const {
		if (this->size != other.size)
			return false;
		return std::memcmp(this->get_data(), other.get_data(), this->size) == 0;
	}
}