#include "message_handler/message_handler.h"

#include "network/p2p_network.h"

namespace sage {

void MessageHandler::PushMessage(RoutingMessagePtr message_ptr) {
	thread_pool_ptr_->enqueue(&MessageHandler::HandleMessage, this, *message_ptr);
}
void MessageHandler::HandleMessage(RoutingMessage const& routing_message) {
	switch ((RoutingMessageType)routing_message.msg_type) {
    case RoutingMessageType::kNodeJoinRequest:
		HandleNodeJoinRequest(routing_message);
		break;
	case RoutingMessageType::kNodeJoinResponse:
		HandleNodeJoinResponse(routing_message);
		break;
	case RoutingMessageType::kHeartBeatRequest:
		HandleHeartbeatRequest(routing_message);
		break;
	case RoutingMessageType::kHeartBeatResponse:
		HandleHeartbeatResponse(routing_message);
		break;
	default:
		assert(0);
		break;
	}
}

void MessageHandler::HandleNodeJoinRequest(RoutingMessage const& routing_message) {
}

void MessageHandler::HandleNodeJoinResponse(RoutingMessage const& routing_message) {

}

void MessageHandler::HandleHeartbeatRequest(RoutingMessage const& routing_message) {

}

void MessageHandler::HandleHeartbeatResponse(RoutingMessage const& routing_message) {

}

}