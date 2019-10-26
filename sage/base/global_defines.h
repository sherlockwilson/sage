#pragma once

#include "boost/asio.hpp"

namespace sage {

using TransportMessageHandler = std::function<std::string(std::string const&, boost::asio::ip::udp::endpoint const&)>;

}