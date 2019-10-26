#include "message_handler/message_handler.h"

namespace sage {

MessageHandler& MessageHandler::Instance() {
	static MessageHandler ins;
	return ins;
}

void MessageHandler::PushMessage(RoutingMessagePtr message_ptr) {
	std::lock_guard<std::mutex> lock(mutex_);
	message_queue_.push(std::move(message_ptr));
}

void MessageHandler::Exec(RoutingMessage const& routing_message,
	                      RoutingTablePtr routing_table_ptr) {
	return HandleMessage(routing_message, routing_table_ptr);
}

void MessageHandler::HandleMessage(RoutingMessage const& routing_message, 
	                               RoutingTablePtr routing_table_ptr) {
	switch ((RoutingMessageType)routing_message.msg_type) {
	case RoutingMessageType::kBootStrapRequest:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kBootStrapResponse:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
    case RoutingMessageType::kNodeJoinRequest:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kNodeJoinResponse:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kHeartBeatRequest:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kHeartBeatResponse:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	default:
		assert(0);
		break;
	}
}

void MessageHandler::HandleBootstrapRequest(RoutingMessage const& routing_message, 
	                                        RoutingTablePtr routing_table_ptr) {

}

void MessageHandler::HandleBootstrapResponse(RoutingMessage const& routing_message, 
	                                         RoutingTablePtr routing_table_ptr) {

}

void MessageHandler::HandleNodeJoinRequest(RoutingMessage const& routing_message, 
	                                       RoutingTablePtr routing_table_ptr) {

}

void MessageHandler::HandleNodeJoinResponse(RoutingMessage const& routing_message, 
	                                        RoutingTablePtr routing_table_ptr) {

}

void MessageHandler::HandleHeartbeatRequest(RoutingMessage const& routing_message, 
	                                        RoutingTablePtr routing_table_ptr) {

}

void MessageHandler::HandleHeartbeatResponse(RoutingMessage const& routing_message, 
	                                         RoutingTablePtr routing_table_ptr) {

}

}