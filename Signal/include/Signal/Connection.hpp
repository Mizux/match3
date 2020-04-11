//! @file
#pragma once

#include <functional>

namespace Signal {

//! @brief Save connection between on Observer and a Signal or Property.
//! @details Will automatically destroy the connection at object destruction.
class Connection {
	public:
	Connection(std::function<void(void)>&& deconnector)
	  : _deconnector(deconnector) {}
	Connection(const Connection&) = delete;             // no cpyable
	Connection& operator=(const Connection&) = delete;  // no cpy op
	Connection(Connection&&)                 = default; // movable
	Connection& operator=(Connection&&) = default;      // movable op

	~Connection() { disconnect(); }

	inline void disconnect() const { _deconnector(); }

	private:
	std::function<void(void)> _deconnector;
};
} // namespace Signal
