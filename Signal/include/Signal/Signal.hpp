//! @file
#pragma once

#include "Connection.hpp"
#include <functional>
#include <memory>

namespace Signal {

template <typename... T>
class SignalImpl;

//! @brief Signal.
//! @details Feature:
//! - Be able to Disconnect at any time (even if signal has been destroy).
//! Thus, I use a shared_ptr as PImpl so Connection can track with a weak_ptr if
//! SignalImpl is still alive.
template <typename... T>
class Signal {
	public:
	using Observer = std::function<void(const T&...)>;

	Signal();
	virtual ~Signal()     = default;
	Signal(const Signal&) = delete;             // no cpyable
	Signal& operator=(const Signal&) = delete;  // no cpy op
	Signal(Signal&&)                 = default; // movable
	Signal& operator=(Signal&&) = default;      // movable op

	template <class ObserverType>
	Connection connect(ObserverType&& observer);
	template <class U>
	Connection connect(U* obj, void (U::*func)(const T&...));

	template <class... CallArgs>
	void emit(CallArgs&&... args) const;

	//! @brief Return the number of current Observers.
	size_t size() const;
	bool empty() const;

	private:
	//! @brief PImpl idiom
	//! Use of shared_ptr so @see Connection
	std::shared_ptr<SignalImpl<T...>> _private;
};
} // namespace Signal

#include "details/Signal.hxx"
