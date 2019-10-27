#pragma once

#include "boost/noncopyable.hpp"

#include "base/thread_pool.h"
#include "network/udp_client.h"
#include "network/udp_server.h"
#include "routing_table/routing_table.h"
#include "message_handler/message_handler.h"

namespace sage {

class P2PNetwork : public boost::noncopyable {
public:
	explicit P2PNetwork(ThreadPoolPtr thread_pool_ptr) {
		message_handler_ptr_.reset(new MessageHandler(std::move(thread_pool_ptr)));
	}
	virtual ~P2PNetwork() = default;

	void Init(std::string const& config_path);

	void UnInit();

	void Bootstrap();

	void NodeJoin();

	void Heartbeat();

	void SendRecurve(std::string const& target_id);

	//for test
	std::string ID() const { return id_; }
	std::vector<std::string> GetAllNodes() const;

private:

	std::string       id_;
	std::string       root_ip_;
	int32_t           root_port_;
	std::string       local_ip_;
	int32_t           local_port_;
	UdpClientPtr      client_ptr_;
	UdpServerPtr      server_ptr_;
	RoutingTablePtr   routing_table_ptr_;
	MessageHandlerPtr message_handler_ptr_;
};

using P2PNetworkPtr = std::shared_ptr<P2PNetwork>;

}