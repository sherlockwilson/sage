#pragma once

#include "boost/noncopyable.hpp"
#include "cmd/Console.hpp"
#include "network/p2p_network.h"

namespace sage {

class CmdHandler : public boost::noncopyable {
public:
	CmdHandler();
	virtual ~CmdHandler() = default;

	void Init(P2PNetworkPtr p2pnetwork_ptr);

	void DoCmd(std::string const& cmd_line);
private:

	int PrintRoutingTable(CppReadline::Console::Arguments const& args);

	std::unique_ptr<CppReadline::Console> console_ptr_;
	P2PNetworkPtr                         p2pnetwork_ptr_;
};

}