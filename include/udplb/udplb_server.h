#ifndef UDP_LowBandwidth_SERVER_EXPORTS
#define UDP_LowBandwidth_SERVER_EXPORTS
#include "udplb_common.h"
#include "udplb_client.h"
namespace udp_low_bandwidth{
	// These are for the implementation of this library
	struct server_data;
	typedef struct server_data server_data_t;

	class Server;

	// You need to subclass this class to create a server
	// Define the callback function to handle incoming packets
	class Server{
	private:
		server_data_t* impl;
	public:
		// User defined (you need to override these functions)
		/**
		 * @brief This function is called when a packet is received
		 *
		 * @param client The client that sent the packet
		 * @param data The data in the packet
		 * @param size The size of the data
		 */
		virtual void callback(Client& client, const std::byte* data, size_t size) = 0;

		/**
		 * @brief This function is called when the server is started before the server starts
		 */
		virtual void on_start() = 0;

		/**
		 * @brief This function is called when the server is stopped after the server stops
		 */
		virtual void on_stop() = 0;


		/**
		 * You should override this function to handle informing the clients of server shutdown
		 * @brief This function is called when the server is stopping for each client
		 *
		 * @param client The client that is being disconnected
		 */
		virtual void stop_disconnect(Client& client) = 0;

		// Library defined (do not override these functions)
		/**
		 * @brief Construct a new Server object
		 *
		 * @param port The port to listen on
		 * @param addr The address to listen on
		 */
		Server(unsigned short port, address* addr);

		/**
		 * @brief Start the server
		 * @note This function is blocking
		 * @note The callback will execute in a new thread
		 * @note This function will return when the server is stopped
		 * @note The only way to stop the server is to call stop()
		 */
		void start();

		/**
		 * @brief Start the server asynchronously
		 * @note This function is non-blocking
		 * @note The callback will execute in a new thread
		 * @note This function will return immediately
		 */
		void start_async();

		/**
		 * @brief Send data to a client
		 *
		 * @param client The client to send the data to
		 * @param data The data to send
		 * @param size The size of the data
		 */
		void send(Client& client, const std::byte* data, size_t size);

		/**
		 * @brief Stop the server
		 * @note This function will return when the server is stopped
		 * @note This function will block until the server is stopped
		 */
		void stop();

		/**
		 * @brief Destroy the Server object
		 *
		 */
		virtual ~Server();
	};
}
#endif