#pragma once

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/noncopyable.hpp"

namespace sage {

class UdpClient : public boost::noncopyable {
public:
	UdpClient() 
		      : sock_(s_ios, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)) {}
	virtual ~UdpClient() = default;
public:
	void Start();
	void SendTo(std::string const& msg,
		        std::string const& ip, 
		        uint16_t port);
private:
	void OnWrite(boost::system::error_code const& err, size_t bytes);
private:
	static const size_t s_buff_size = 1024;
private:
	boost::asio::ip::udp::socket sock_;
public:
	static boost::asio::io_service s_ios;
};

using UdpClientPtr = std::shared_ptr<UdpClient>;

}