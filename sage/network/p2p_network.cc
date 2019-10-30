#include "network/p2p_network.h"

#include <assert.h>
#include "config/inifile.h"

namespace sage {

void P2PNetwork::Init(std::string const& config_path) {
	inifile::IniFile ini;
	assert(0 == ini.Load(config_path));
	assert(0 == ini.GetStringValue("COMMON","ROOT_IP"   ,&root_ip_));
	assert(0 == ini.GetIntValue("COMMON"   ,"ROOT_PORT" ,&root_port_));
	assert(0 == ini.GetIntValue("COMMON"   ,"LOCAL_PORT",&local_port_));
	assert(0 == ini.GetStringValue("COMMON","ID"        ,&id_));
	assert(0 == ini.GetIntValue("COMMON"   ,"WORK_ID"   ,&worker_id_));
	assert(0 == ini.GetIntValue("COMMON"   ,"NETWORK_ID",&data_center_id_));
	client_ptr_.reset(new UdpClient());
	server_ptr_.reset(new UdpServer(local_port_));
	local_ip_ = server_ptr_->IP();
	routing_table_ptr_.reset(new RoutingTable(id_));
	msg_id_generator_.reset(new MessageIDGenerator(worker_id_, data_center_id_));
}

void P2PNetwork::UnInit() {
	client_ptr_.reset();
	server_ptr_.reset();
	routing_table_ptr_.reset();
}

void P2PNetwork::Bootstrap() {
	NodeJoin(root_ip_, root_port_);
}

void  P2PNetwork::NodeJoin(std::string const& ip, int32_t const& port) {
	RoutingMessage message;
	message.message_id = msg_id_generator_->NextID();
	message.msg_type = (uint64_t)RoutingMessageType::kNodeJoinRequest;
	message.from_ip = local_ip_;
	message.from_port = local_port_;
	message.to_ip = ip;
	message.to_port = port;
	SendTo(message);
}

void P2PNetwork::Heartbeat(std::string const& ip, int32_t const& port) {
	RoutingMessage message;
	message.message_id = msg_id_generator_->NextID();
	message.msg_type = (uint64_t)RoutingMessageType::kHeartBeatRequest;
	message.from_ip = local_ip_;
	message.from_port = local_port_;
	message.to_ip = ip;
	message.to_port = port;
	SendTo(message);
}

void P2PNetwork::SendTo(RoutingMessage & message) {
	ByteBuffer byte_buffer;
	message.do_write(byte_buffer);
	auto const& buffer = byte_buffer.getBuffer();
	if (buffer.empty()) {
		return;
	}
	return client_ptr_->SendTo(std::string((char*)buffer.data(), buffer.size()),
		                       message.to_ip,
		                       message.to_port);
}

void P2PNetwork::SendRecurve(RoutingMessage & message,
	                         std::string const& target_id) {
	auto const& closest_nodes = routing_table_ptr_->GetClosestNodes(target_id, 1);
	assert(closest_nodes.size() <= 1);
	if (closest_nodes.empty()) {
		return;
	}
	auto node_ptr = routing_table_ptr_->FindNode(closest_nodes[0]);
	if (NULL == node_ptr) {
		return;
	}
	ByteBuffer byte_buffer;
	message.do_write(byte_buffer);
	auto const& buffer = byte_buffer.getBuffer();
	if (buffer.empty()) {
		return;
	}
	return client_ptr_->SendTo(std::string((char*)buffer.data(), buffer.size()), 
		                       node_ptr->ip_, 
		                       node_ptr->port_);
}

std::vector<std::string> P2PNetwork::GetAllNodes() const {
	return {};
}

}