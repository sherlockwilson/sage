#pragma once

#include <string>
#include <assert.h>

namespace sage {

static bool CloserToTarget(std::string const& left_id,
	std::string const& right_id,
	std::string const& target_id) {
	assert(left_id.size() == right_id.size() && right_id.size() == target_id.size());
	auto const& length = target_id.size();
	for (uint32_t i = 0; i < length; ++i) {
		bool ret1 = left_id[i] ^ target_id[i];
		bool ret2 = right_id[i] ^ target_id[i];
		if (ret1 != ret2) {
			return ret1;
		}
	}
	return true;
}

}