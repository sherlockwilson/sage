#include "routing_table.h"

#include "routing_table_algorithm.h"

namespace sage {

void RoutingTable::UpdateNode(NodeInfo & node_info) {
	std::lock_guard<std::mutex> lock(nodes_mutex_);
	if (id_ == node_info.id_) {
		return;
	}
	auto node_info_ptr = NodeInfoPtr(&node_info);
	nodes_[node_info.id_] = node_info_ptr;
	AddNeighbors(node_info);
}

void RoutingTable::RemoveNode(std::string const& id) {
	std::lock_guard<std::mutex> lock(nodes_mutex_);
	nodes_.erase(id);
	DeleteNeighbors(id);
}

void RoutingTable::AddNeighbors(NodeInfo & node_info) {
	std::lock_guard<std::mutex> lock(neighbors_mutex_);
	if (id_ == node_info.id_) {
		return;
	}
	auto node_info_ptr = NodeInfoPtr(&node_info);
	for (int32_t i = 0;i < neighbors_.size(); ++i) {
		if (neighbors_[i]->id_ == node_info.id_) {
			neighbors_[i] = node_info_ptr;
			return;
		}
		if (CloserToTarget(node_info.id_, neighbors_[i]->id_, id_)) {
			neighbors_.insert(neighbors_.begin() + i, node_info_ptr);
			return;
		}
	}
	neighbors_.push_back(node_info_ptr);
}

void RoutingTable::DeleteNeighbors(std::string const& id) {
	std::lock_guard<std::mutex> lock(neighbors_mutex_);
	if (id_ == id) {
		return;
	}
	for (int32_t i = 0; i < neighbors_.size(); ++i) {
		if (id == neighbors_[i]->id_) {
			neighbors_.erase(neighbors_.begin() + i);
			return;
		}
	}
}

}