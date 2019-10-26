#pragma once

#include <string>
#include <memory>

namespace sage {

struct NodeInfo {
	explicit NodeInfo(std::string const& id, std::string const& ip, uint16_t port)
		:id_(id),
		ip_(ip),
		port_(port) {}
	std::string id_;
	std::string ip_;
	uint16_t    port_;
};

typedef std::shared_ptr<NodeInfo> NodeInfoPtr;

}