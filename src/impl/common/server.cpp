#include "udplb_server.h"
#include <atomic>
#include <vector>
#include <mutex>
#include <thread>
using namespace udp_low_bandwidth;

struct udp_low_bandwidth::server_data{
	unsigned short port;
	address* addr;
	std::atomic<bool> running;
	std::mutex clients_mutex;
	std::vector<Client> clients;
	std::mutex threads_mutex;
	std::vector<std::thread> threads;
};

Server::Server(unsigned short port, address* addr){
	impl = new server_data_t;
	impl->port = port;
	impl->addr = addr;
}

void Server::start() {
	on_start();
	while (impl->running){

	}
	on_stop();
}

Server::~Server(){
	delete impl;
}