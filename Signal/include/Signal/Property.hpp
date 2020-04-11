//! @file
#pragma once

#include "Connection.hpp"
#include <functional>
#include <memory>

namespace Signal {

template <typename T>
class PropertyImpl;

template <typename T>
class Property {
	public:
	using Observer = std::function<void(const T&)>;

	Property();
	explicit Property(T value);
	~Property()                 = default;
	Property(const Connection&) = delete;           // no cpyable
	Property& operator=(const Property&) = delete;  // no cpy op
	Property(Property&&)                 = default; // movable
	Property& operator=(Property&&) = default;      // movable op

	template <typename ObserverType>
	Connection connect(ObserverType&& observer);
	template <class U>
	Connection connect(U* obj, void (U::*func)(const T&));

	T get() const;
	void set(T value);

	std::size_t size() const;
	bool empty() const;

	private:
	std::shared_ptr<PropertyImpl<T>> _private;
};
} // namespace Signal

#include "details/Property.hxx"
