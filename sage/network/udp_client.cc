#include "udp_client.h"

#include <string.h>
#include <iostream>

namespace sage {

boost::asio::io_service UdpClient::s_ios;

void UdpClient::Start() {
	s_ios.run();
}

void UdpClient::SendTo(std::string const& msg,
					   std::string const& ip,
					   uint16_t port) {
	char write_buf[s_buff_size] = {0};
	copy(begin(msg), end(msg), write_buf);
	sock_.async_send_to(boost::asio::buffer(write_buf, msg.size()), { boost::asio::ip::address::from_string(ip), port },
		                boost::bind(&UdpClient::OnWrite, this, _1, _2));
}

void UdpClient::OnWrite(boost::system::error_code const& err, size_t bytes) {}

}