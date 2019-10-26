#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "node_info.h"

namespace sage {

class RoutingTable {
public:
	RoutingTable() {}
	~RoutingTable() {}

	void UpdateNode(NodeInfo & node_info);

	void RemoveNode(std::string const& id);

private:

	void AddNeighbors(NodeInfo & node_info);

	void DeleteNeighbors(std::string const& id);

	std::mutex                         neighbors_mutex_;
	std::mutex                         nodes_mutex_;
	std::string                        id_;
	std::vector<NodeInfoPtr>           neighbors_;
	std::map<std::string, NodeInfoPtr> nodes_;
};

}