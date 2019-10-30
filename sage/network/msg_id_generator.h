#pragma once

#include <memory>
#include "base/id.h"

namespace sage {

class MessageIDGenerator {
public:
	explicit MessageIDGenerator(uint16_t worker_id, uint16_t data_center_id)
		     :msg_id_generator_(new snowflake4cxx::IdWorkerThreadSafe(worker_id, data_center_id)){}
	virtual ~MessageIDGenerator() = default;
	uint64_t NextID() { return msg_id_generator_->GetNextID(); }
private:
	std::unique_ptr<snowflake4cxx::IdWorkerThreadSafe> msg_id_generator_;
};

using MessageIDGeneratorPtr = std::unique_ptr<MessageIDGenerator>;

}