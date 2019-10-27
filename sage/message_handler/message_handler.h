#pragma once

#include <memory>
#include <queue>

#include "boost/noncopyable.hpp"
#include "base/global_defines.h"
#include "base/thread_pool.h"
#include "routing_table/routing_table.h"

namespace sage {

class MessageHandler : public boost::noncopyable {
public:
    explicit MessageHandler(ThreadPoolPtr thread_pool_ptr) :thread_pool_ptr_(std::move(thread_pool_ptr)) {}
	virtual ~MessageHandler() = default;

	void PushMessage(RoutingMessagePtr message_ptr, 
		             RoutingTablePtr routing_table_ptr);

private:

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

	ThreadPoolPtr                 thread_pool_ptr_;
};

using MessageHandlerPtr = std::unique_ptr<MessageHandler>;

}