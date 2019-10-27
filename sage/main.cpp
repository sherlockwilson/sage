#include <cstdio>
#include <iostream>

#include "base/thread_pool.h"
#include "network/p2p_network.h"
#include "cmd/cmd_parser.h"

using namespace sage;

int main()
{
	CmdHandler    cmd_handler;
	ThreadPoolPtr thread_pool_ptr;
	thread_pool_ptr.reset(new ThreadPool());
	P2PNetworkPtr p2pnetwork_ptr;
	p2pnetwork_ptr.reset(new P2PNetwork(std::move(thread_pool_ptr)));
	p2pnetwork_ptr->Init("./config.ini");
	cmd_handler.Init(p2pnetwork_ptr);
	while (true) {
		std::string cmd_line;
		std::getline(std::cin, cmd_line);
		if ("exit" == cmd_line) {
			break;
		}
		cmd_handler.DoCmd(cmd_line);
	}

	p2pnetwork_ptr->UnInit();
    return 0;
}