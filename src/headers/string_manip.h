#pragma once
#include <string>
#include <vector>

namespace udp_low_bandwidth::string_manip{

	/**
	 *
	 * @brief Splits a string into a vector of strings based on a delimiter
	 * @param str The string to split
	 * @param delimiter The delimiter to split the string by
	 * @return A vector of strings
	 */
	 std::vector<std::string> split(const std::string& str, const std::string& delimiter);

	 /**
	  * @brief Converts a byte to a hex string
	  * @param byte The byte to convert
	  * @return A hex string
	  */
	 std::string to_hex(const std::byte& byte);

	 /**
	  * @brief Converts a byte to a decimal string
	  * @param byte The byte to convert
	  * @return A decimal string
	  */
	 std::string to_dec(const std::byte& byte);
}