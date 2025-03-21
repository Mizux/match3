//! @file
#pragma once

#include "../Signal.hpp"

#include <cstdint>
#include <unordered_map>

namespace Signal {

template <typename... T>
class SignalImpl {
	public:
	using Observer = std::function<void(const T&...)>;

	SignalImpl()                  = default;
	~SignalImpl()                 = default;
	SignalImpl(const SignalImpl&) = delete;             // no cpyable
	SignalImpl& operator=(const SignalImpl&) = delete;  // no cpy op
	SignalImpl(SignalImpl&&)                 = default; // movable
	SignalImpl& operator=(SignalImpl&&) = default;      // movable op

	template <class ObserverType>
	std::uint32_t connect(ObserverType&& observer);
	template <class U>
	std::uint32_t connect(U* obj, void (U::*func)(const T&...));
	void disconnect(std::uint32_t uid);

	template <class... CallArgs>
	void emit(CallArgs&&... args) const;

	std::size_t size() const;
	bool empty() const;

	private:
	std::uint32_t _uid;
	std::unordered_map<std::uint32_t, Observer> _observers;
};

//////////////
//  SIGNAL  //
//////////////
template <typename... T>
Signal<T...>::Signal()
  : _private(std::make_shared<SignalImpl<T...>>()) {}

template <typename... T>
template <class ObserverType>
Connection
Signal<T...>::connect(ObserverType&& observer) {
	std::uint32_t uid                  = this->_private->connect(observer);
	std::weak_ptr<SignalImpl<T...>> wp = this->_private;
	return Connection([=]() {
		auto sp = wp.lock();
		if (sp != nullptr) {
			sp->disconnect(uid);
		}
	});
}

template <typename... T>
template <class U>
Connection
Signal<T...>::connect(U* obj, void (U::*func)(const T&...)) {
	std::uint32_t uid                  = this->_private->connect(obj, func);
	std::weak_ptr<SignalImpl<T...>> wp = this->_private;
	return Connection([=]() {
		auto sp = wp.lock();
		if (sp != nullptr) {
			sp->disconnect(uid);
		}
	});
}

template <typename... T>
template <class... CallArgs>
void
Signal<T...>::emit(CallArgs&&... args) const {
	this->_private->emit(args...);
}

template <typename... T>
std::size_t
Signal<T...>::size() const {
	return this->_private->size();
}

template <typename... T>
bool
Signal<T...>::empty() const {
	return this->_private->empty();
}

///////////////////
//  SIGNAL IMPL  //
///////////////////
template <typename... T>
template <class ObserverType>
std::uint32_t
SignalImpl<T...>::connect(ObserverType&& observer) {
	std::uint32_t uid = this->_uid++;
	this->_observers.insert({uid, std::forward<ObserverType>(observer)});
	return uid;
}

template <typename... T>
template <class U>
std::uint32_t
SignalImpl<T...>::connect(U* obj, void (U::*func)(const T&...)) {
	return connect([=](const T&... args) { (obj->*func)(args...); });
}

template <typename... T>
void
SignalImpl<T...>::disconnect(std::uint32_t uid) {
	this->_observers.erase(uid);
}

template <typename... T>
template <class... CallArgs>
void
SignalImpl<T...>::emit(CallArgs&&... args) const {
	for (auto const& observer : this->_observers) {
		observer.second(args...);
	}
}

template <typename... T>
std::size_t
SignalImpl<T...>::size() const {
	return this->_observers.size();
}

template <typename... T>
bool
SignalImpl<T...>::empty() const {
	return this->_observers.empty();
}
} // namespace Signal
