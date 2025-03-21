//! @file
#pragma once

#include "../Property.hpp"

#include <cstdint>
#include <unordered_map>

namespace Signal {

template <typename T>
class PropertyImpl {
	public:
	using Observer = std::function<void(const T&)>;

	PropertyImpl() = default;
	explicit PropertyImpl(T value)
	  : _value(std::move(value))
	  , _uid(0)
	  , _observers() {}
	~PropertyImpl()                   = default;
	PropertyImpl(const PropertyImpl&) = delete;             // no cpyable
	PropertyImpl& operator=(const PropertyImpl&) = delete;  // no cpy op
	PropertyImpl(PropertyImpl&&)                 = default; // movable
	PropertyImpl& operator=(PropertyImpl&&) = default;      // movable op

	template <typename ObserverType>
	std::uint32_t connect(ObserverType&& observer);
	template <class U>
	std::uint32_t connect(U* obj, void (U::*func)(const T&));
	void disconnect(std::uint32_t uid);

	const T& get() const;
	void set(T value);

	std::size_t size() const;
	bool empty() const;

	private:
	T _value;
	std::uint32_t _uid;
	std::unordered_map<std::uint32_t, Observer> _observers;
};

////////////////
//  PROPERTY  //
////////////////
template <typename T>
Property<T>::Property()
  : _private(std::make_shared<PropertyImpl<T>>()) {}

template <typename T>
Property<T>::Property(T value)
  : _private(std::make_shared<PropertyImpl<T>>(std::move(value))) {}

template <typename T>
template <class ObserverType>
Connection
Property<T>::connect(ObserverType&& observer) {
	std::uint32_t uid                 = this->_private->connect(observer);
	std::weak_ptr<PropertyImpl<T>> wp = this->_private;
	return Connection([=]() {
		auto sp = wp.lock();
		if (sp != nullptr) {
			sp->disconnect(uid);
		}
	});
}

template <typename T>
template <class U>
Connection
Property<T>::connect(U* obj, void (U::*func)(const T&)) {
	std::uint32_t uid                 = this->_private->connect(obj, func);
	std::weak_ptr<PropertyImpl<T>> wp = this->_private;
	return Connection([=]() {
		auto sp = wp.lock();
		if (sp != nullptr) {
			sp->disconnect(uid);
		}
	});
}

template <typename T>
T
Property<T>::get() const {
	return this->_private->get();
}

template <typename T>
void
Property<T>::set(T value) {
	this->_private->set(std::move(value));
}

template <typename T>
std::size_t
Property<T>::size() const {
	return this->_private->size();
}

template <typename T>
bool
Property<T>::empty() const {
	return this->_private->empty();
}

/////////////////////
//  PROPERTY IMPL  //
/////////////////////
template <typename T>
template <class ObserverType>
std::uint32_t
PropertyImpl<T>::connect(ObserverType&& observer) {
	std::uint32_t uid = this->_uid++;
	this->_observers.insert({uid, std::forward<ObserverType>(observer)});
	return uid;
}

template <typename T>
template <class U>
std::uint32_t
PropertyImpl<T>::connect(U* obj, void (U::*func)(const T&)) {
	return connect([=](const T& arg) { (obj->*func)(arg); });
}

template <typename T>
void
PropertyImpl<T>::disconnect(std::uint32_t uid) {
	this->_observers.erase(uid);
}

template <typename T>
const T&
PropertyImpl<T>::get() const {
	return this->_value;
}

template <typename T>
void
PropertyImpl<T>::set(T value) {
	this->_value = value;
	for (auto const& observer : this->_observers) {
		observer.second(this->_value);
	}
}

template <typename T>
std::size_t
PropertyImpl<T>::size() const {
	return this->_observers.size();
}

template <typename T>
bool
PropertyImpl<T>::empty() const {
	return this->_observers.empty();
}
} // namespace Signal
