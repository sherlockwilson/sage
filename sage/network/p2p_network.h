#pragma once

#include "boost/noncopyable.hpp"

#include "network/udp_client.h"
#include "network/udp_server.h"
#include "routing_table/routing_table.h"

namespace sage {

class P2PNetwork : public boost::noncopyable {
public:
	P2PNetwork() = default;
	virtual ~P2PNetwork() = default;

	void Init(std::string const& config_path);

	void UnInit();

	void SendRecurve(std::string const& target_id);

	void Bootstrap();

	void NodeJoin();

	void Heartbeat();

private:
	std::string     id_;
	std::string     root_ip_;
	int32_t         root_port_;
	std::string     local_ip_;
	int32_t         local_port_;
	UdpClientPtr    client_ptr_;
	UdpServerPtr    server_ptr_;
	RoutingTablePtr routing_table_ptr_;
};

}