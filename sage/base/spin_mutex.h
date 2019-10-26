#pragma once

#include <atomic>

namespace sage {

class spin_mutex {
public:
	spin_mutex() = default;
	spin_mutex(const spin_mutex&) = delete;
	spin_mutex& operator= (const spin_mutex&) = delete;
	void lock() {
		bool expected = false;
		while (!flag_.compare_exchange_strong(expected, true)) {
			expected = false;
		}
	}
	void unlock() {
		flag_.store(false);
	}
private:
	std::atomic<bool> flag_{ ATOMIC_VAR_INIT(false) };
};

}