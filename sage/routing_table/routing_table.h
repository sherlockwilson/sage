#pragma once

#include <map>
#include <vector>
#include <mutex>

#include "routing_table/node_info.h"
#include "boost/noncopyable.hpp"

namespace sage {

class RoutingTable : public boost::noncopyable {
public:
	explicit RoutingTable(std::string const& id):id_(id) {}
	~RoutingTable() {}

	void UpdateNode(NodeInfo & node_info);

	void RemoveNode(std::string const& id);

	NodeInfoPtr FindNode(std::string const& node_id);

	auto GetClosestNodes(std::string const& target_id, 
		                 uint32_t num) -> std::vector<std::string>;

private:

	void AddNeighbors(NodeInfo & node_info);

	void DeleteNeighbors(std::string const& id);

	std::mutex                         neighbors_mutex_;
	std::mutex                         nodes_mutex_;
	std::string                        id_;
	std::vector<NodeInfoPtr>           neighbors_;
	std::map<std::string, NodeInfoPtr> nodes_;
};

using RoutingTablePtr = std::shared_ptr<RoutingTable>;

}