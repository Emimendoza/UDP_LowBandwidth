#ifndef UDP_LowBandwidth_CLIENT_EXPORTS
#define UDP_LowBandwidth_CLIENT_EXPORTS
#include "udplb_common.h"
namespace udp_low_bandwidth
{
	class Client
	{
	protected:
		/**
		 * @brief Incoming port
		 */
		port port;
		/**
		 * @brief Incoming address
		 */
		address* addr;
		/**
		 * @brief The server to connect to
		 */
		Server* server;
	public:
		Client();
		~Client();
	};
}
#endif


