#include "udp_server.h"

namespace sage {

boost::asio::io_service UdpServer::s_ios;

void UdpServer::Start(TransportMessageHandler recv_fun) {
	 recv_fun_ = recv_fun;
	 DoRead();
	 s_ios.run();
}

void UdpServer::OnRead(const boost::system::error_code &err, size_t bytes) {
	if (!err) {
		std::string msg(read_buf_, bytes);
		auto const& reply_msg = recv_fun_(msg, sender_end_point_);
		DoWrite(reply_msg);
	}
}

void UdpServer::DoRead() {
	sock_.async_receive_from(boost::asio::buffer(read_buf_), 
		                     sender_end_point_, 
		                     boost::bind(&UdpServer::OnRead, this, _1, _2));
}

void UdpServer::OnWrite(const boost::system::error_code &err, size_t bytes) {
	DoRead();
}

void UdpServer::DoWrite(const std::string &msg) {
	std::copy(begin(msg), end(msg), write_buf_);
	sock_.async_send_to(boost::asio::buffer(write_buf_, msg.size()),
		                sender_end_point_, boost::bind(&UdpServer::OnWrite, this, _1, _2));
}

}