#pragma once

#include <string>

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/noncopyable.hpp"
#include "base/global_defines.h"

namespace sage {

class UdpServer : public boost::noncopyable {
public:
	explicit UdpServer(uint16_t port)
		      : sock_(s_ios, 
				      boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 
					  port)) {}

	virtual ~UdpServer() = default;
public:
	void Start(TransportMessageHandler recv_func);

	std::string IP() { return sock_.local_endpoint().address().to_string(); }
	uint16_t Port() { return sock_.local_endpoint().port(); }

private:
	void OnRead(const boost::system::error_code &err, size_t bytes);
	void DoRead();
	void OnWrite(const boost::system::error_code &err, size_t bytes);
	void DoWrite(const std::string &msg);
private:
	static const size_t s_buff_size = 1024;
private:
	char write_buf_[s_buff_size];
	char read_buf_[s_buff_size];
	boost::asio::ip::udp::endpoint sender_end_point_;
	boost::asio::ip::udp::socket   sock_;
	TransportMessageHandler recv_fun_;
public:
	static boost::asio::io_service s_ios;
};

using UdpServerPtr = std::shared_ptr<UdpServer>;

}