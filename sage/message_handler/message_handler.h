#pragma once

#include <memory>
#include <queue>

#include "boost/noncopyable.hpp"
#include "base/global_defines.h"
#include "base/thread_pool.h"

namespace sage {

class P2PNetwork;
using P2PNetworkPtr = std::shared_ptr<P2PNetwork>;

class MessageHandler : public boost::noncopyable {
public:
    explicit MessageHandler(ThreadPoolPtr thread_pool_ptr, P2PNetworkPtr network_ptr) 
		                    :thread_pool_ptr_(std::move(thread_pool_ptr)), 
		                     network_ptr_(network_ptr) {}
	virtual ~MessageHandler() = default;

	void PushMessage(RoutingMessagePtr message_ptr);

private:

	void HandleMessage(RoutingMessage const& routing_message);

	void HandleNodeJoinRequest(RoutingMessage const& routing_message);

	void HandleNodeJoinResponse(RoutingMessage const& routing_message);

	void HandleHeartbeatRequest(RoutingMessage const& routing_message);

	void HandleHeartbeatResponse(RoutingMessage const& routing_message);

	ThreadPoolPtr                 thread_pool_ptr_;
	P2PNetworkPtr                 network_ptr_;
};

using MessageHandlerPtr = std::unique_ptr<MessageHandler>;

}