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
	client_ptr_.reset(new UdpClient());
	server_ptr_.reset(new UdpServer(local_port_));
	local_ip_ = server_ptr_->IP();
	routing_table_ptr_.reset(new RoutingTable(id_));
}

void P2PNetwork::UnInit() {
	client_ptr_.reset();
	server_ptr_.reset();
	routing_table_ptr_.reset();
}

void P2PNetwork::Bootstrap() {
}

void P2PNetwork::NodeJoin() {
}

void P2PNetwork::Heartbeat() {
}

void P2PNetwork::SendRecurve(std::string const& target_id) {
}

std::vector<std::string> P2PNetwork::GetAllNodes() const {
	return {};
}

}