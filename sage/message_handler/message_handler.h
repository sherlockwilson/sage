#pragma once

#include <memory>
#include <queue>

#include "base/global_defines.h"
#include "routing_table/routing_table.h"

namespace sage {

class MessageHandler {
public:
	static MessageHandler& Instance();

	void PushMessage(RoutingMessagePtr message_ptr);

private:
	MessageHandler() = default;
	~MessageHandler() = default;

	void Exec(RoutingMessage const& routing_message, 
		      RoutingTablePtr routing_table_ptr);

	void HandleMessage(RoutingMessage const& routing_message, 
		               RoutingTablePtr routing_table_ptr);

	void HandleBootstrapRequest(RoutingMessage const& routing_message, 
		                        RoutingTablePtr routing_table_ptr);

	void HandleBootstrapResponse(RoutingMessage const& routing_message, 
		                         RoutingTablePtr routing_table_ptr);

	void HandleNodeJoinRequest(RoutingMessage const& routing_message, 
		                       RoutingTablePtr routing_table_ptr);

	void HandleNodeJoinResponse(RoutingMessage const& routing_message, 
		                        RoutingTablePtr routing_table_ptr);

	void HandleHeartbeatRequest(RoutingMessage const& routing_message, 
		                        RoutingTablePtr routing_table_ptr);

	void HandleHeartbeatResponse(RoutingMessage const& routing_message, 
		                         RoutingTablePtr routing_table_ptr);

	std::queue<RoutingMessagePtr> message_queue_;
	std::mutex                    mutex_;
};

}