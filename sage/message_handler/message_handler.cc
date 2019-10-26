#include "message_handler/message_handler.h"

namespace sage {

void MessageHandler::PushMessage(RoutingMessagePtr message_ptr) {
	message_queue_.push(std::move(message_ptr));
}

void MessageHandler::Exec(RoutingMessage const& routing_message) {

}

void MessageHandler::HandleMessage(RoutingMessage const& routing_message) {

}

void MessageHandler::HandleBootstrapRequest(RoutingMessage const& routing_message) {

}

void MessageHandler::HandleBootstrapResponse(RoutingMessage const& routing_message) {

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