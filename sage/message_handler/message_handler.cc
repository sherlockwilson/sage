#include "message_handler/message_handler.h"

namespace sage {

void MessageHandler::PushMessage(RoutingMessagePtr message_ptr, 
	                             RoutingTablePtr routing_table_ptr) {
	thread_pool_ptr_->enqueue(&MessageHandler::HandleMessage, 
		                      this, *message_ptr, routing_table_ptr);
}
void MessageHandler::HandleMessage(RoutingMessage const& routing_message, 
	                               RoutingTablePtr routing_table_ptr) {
	switch ((RoutingMessageType)routing_message.msg_type) {
	case RoutingMessageType::kBootStrapRequest:
		HandleBootstrapRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kBootStrapResponse:
		HandleBootstrapResponse(routing_message, routing_table_ptr);
		break;
    case RoutingMessageType::kNodeJoinRequest:
		HandleNodeJoinRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kNodeJoinResponse:
		HandleNodeJoinResponse(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kHeartBeatRequest:
		HandleHeartbeatRequest(routing_message, routing_table_ptr);
		break;
	case RoutingMessageType::kHeartBeatResponse:
		HandleHeartbeatResponse(routing_message, routing_table_ptr);
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