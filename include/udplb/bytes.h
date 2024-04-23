#ifndef UDP_LowBandwidth_BYTES_EXPORTS
#define UDP_LowBandwidth_BYTES_EXPORTS
#include <cstdint>
#include <memory>
#include <vector>

namespace udp_low_bandwidth{
	/**
	 * @brief Bytes storage class
	 */
	class bytes{
	private:
		std::shared_ptr<std::byte> data = nullptr;
		uint64_t offset = 0; // Only used in views
		uint64_t size = 0;
		[[nodiscard]] inline std::byte* get_data() const{
			return data.get() + offset;
		}

		/**
		 * @brief Creates an empty bytes object
		 */
		bytes() = default;
	public:
		/**
		 * @brief Appends src to right of dest
		 * @param dest The destination
		 * @param src The source
		 */
		void append(const bytes& src);

		 /**
		  * @brief Slices the bytes object
		  * @note The slice is from start to end - 1
		  * @throws std::invalid_argument if start > end
		  * @throws std::out_of_range if start or end is greater than the size of the bytes object
		  * @note If compiled with UDP_LowBandwidth_NO_BOUNDS_CHECK, the bounds check will be disabled
		  * @param start start of the slice
		  * @param end end of the slice
		  * @return a view of the object
		  */
		[[nodiscard]] bytes slice(uint16_t start, uint16_t end) const{
			 #ifndef UDP_LowBandwidth_NO_BOUNDS_CHECK
			 if (start > end)
				 throw std::invalid_argument("The start index must be less than or equal to the end index");
			 if (end > this->size)
				 throw std::out_of_range("The end index must be less than or equal to the size of the bytes object");
			 if (start > this->size)
				 throw std::out_of_range("The start index must be less than or equal to the size of the bytes object");
			 #endif
			 bytes new_bytes;
			 new_bytes.offset = start + this->offset;
			 new_bytes.size = end - new_bytes.offset;
			 return new_bytes;
		}
		/**
		 * @brief Creates a bytes object from another bytes object
		 * @param src The source bytes object
		 */
		bytes(const bytes& src);

		/**
		 * @brief Creates a bytes object of the specified size
		 * @param size The size of the bytes object
		 */
		explicit bytes(uint64_t size);

		/**
		 * @brief Creates a bytes object from a pointer to a byte array
		 * @note The byte array will be copied
		 * @param data The pointer to the byte array
		 * @param size The size of the byte array
		 */
		bytes(const std::byte* data, uint64_t size);

		/**
		 * @brief Creates a bytes object from a pointer to a byte array
		 * @note The byte array will be copied
		 * @param data The pointer to the byte array
		 * @param size The size of the byte array
		 */
		bytes(const uint8_t* data, uint64_t size);

		/**
		 * @brief Creates a bytes object from a vector of bytes objects
		 * @note Equivalent to appending all the bytes objects in the vector to a new bytes object
		 * @throws std::length_error if the size of the bytes object is too large
		 * @param data The vector of bytes objects
		 * @return The bytes object
		 */
		explicit bytes(const std::vector<bytes>& data);

		/**
		 * @brief Compares two bytes objects
		 * @param other The other bytes object
		 * @return true if the two bytes objects hold equal values, false otherwise
		 */
		bool operator == (const bytes& other) const;

		/**
		 * @brief Gets the nth byte in the bytes object
		 * @throws std::out_of_range if the index is greater than or equal to the size of the bytes object
		 * @note If compiled with UDP_LowBandwidth_NO_BOUNDS_CHECK, the bounds check will be disabled
		 * @param index index of the byte
		 * @return The byte at the index
		 */
		std::byte& operator[](uint64_t index) const{
			#ifndef UDP_LowBandwidth_NO_BOUNDS_CHECK
			if (index >= size)
				throw std::out_of_range("Index out of range");
			#endif
			return get_data()[index];
		}

		/**
		 * @brief Gets the size of the bytes object
		 * @return The size of the bytes object
		 */
		[[nodiscard]] uint64_t get_size() const{
			return size;
		}
	};

}

#endif