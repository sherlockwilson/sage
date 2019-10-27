#include "cmd/cmd_parser.h"


using ret = CppReadline::Console::ReturnCode;

namespace sage {

CmdHandler::CmdHandler() {
	console_ptr_.reset(new CppReadline::Console(">"));
	
	console_ptr_->registerCommand("prt", std::bind(&CmdHandler::PrintRoutingTable, this, std::placeholders::_1));
}

void CmdHandler::Init(P2PNetworkPtr p2pnetwork_ptr) {
	p2pnetwork_ptr_ = p2pnetwork_ptr;
}

void CmdHandler::DoCmd(std::string const& cmd_line) {
	console_ptr_->executeCommand(cmd_line);
}

int  CmdHandler::PrintRoutingTable(CppReadline::Console::Arguments const& args) {
	auto const& id        = p2pnetwork_ptr_->ID();
	auto const& all_nodes = p2pnetwork_ptr_->GetAllNodes();
	printf("root id:%s\n", id.c_str());
	for (int i = 0; i < all_nodes.size(); ++i) {
		printf("[i] %s\n", all_nodes[i].c_str());
	}
	return 0;
}

}