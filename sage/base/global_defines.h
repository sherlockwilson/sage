#pragma once

#include "boost/asio.hpp"
#include "base/ByteBuffer.h"

namespace sage {

using TransportMessageHandler = std::function<std::string(std::string const&, boost::asio::ip::udp::endpoint const&)>;

enum class RoutingMessageType {
	kNodeJoinRequest   = 0,
	kNodeJoinResponse  = 1,
	kHeartBeatRequest  = 2,
	kHeartBeatResponse = 3,
};

struct RoutingMessage {
	RoutingMessage() = default;
	virtual ~RoutingMessage() = default;

	void do_read(ByteBuffer & byte_buffer) {
		byte_buffer << message_id;
		byte_buffer << from_ip;
		byte_buffer << from_port;
		byte_buffer << to_ip;
		byte_buffer << to_port;
		byte_buffer << msg_type;
		byte_buffer << data;
	}

	void do_write(ByteBuffer & byte_buffer) {
		byte_buffer >> message_id;
		byte_buffer >> from_ip;
		byte_buffer >> from_port;
		byte_buffer >> to_ip;
		byte_buffer >> to_port;
		byte_buffer >> msg_type;
		byte_buffer >> data;
	}

	std::string message_id;
	std::string from_ip;
	int32_t     from_port;
	std::string to_ip;
	int32_t     to_port;
	uint64_t    msg_type;
	std::string data;
};

using RoutingMessagePtr = std::unique_ptr<RoutingMessage>;

}