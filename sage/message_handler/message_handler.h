#pragma once

#include <memory>
#include <queue>

#include "base/global_defines.h"
#include "routing_table/routing_table.h"

namespace sage {

class MessageHandler {
public:
	explicit MessageHandler(RoutingTablePtr routing_table_ptr):routing_table_ptr_(routing_table_ptr){}
	virtual ~MessageHandler() = default;

	void PushMessage(RoutingMessagePtr message_ptr);

private:
	void Exec(RoutingMessage const& routing_message);
	void HandleMessage(RoutingMessage const& routing_message);
	void HandleBootstrapRequest(RoutingMessage const& routing_message);
	void HandleBootstrapResponse(RoutingMessage const& routing_message);
	void HandleNodeJoinRequest(RoutingMessage const& routing_message);
	void HandleNodeJoinResponse(RoutingMessage const& routing_message);
	void HandleHeartbeatRequest(RoutingMessage const& routing_message);
	void HandleHeartbeatResponse(RoutingMessage const& routing_message);

	RoutingTablePtr               routing_table_ptr_;
	std::queue<RoutingMessagePtr> message_queue_;
};

}