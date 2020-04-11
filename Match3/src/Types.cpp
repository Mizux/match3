//! @file

#include <Match3/Types.hpp>
#include <exception>
#include <string>

namespace match3 {

Types::Types(const Type& type)
  : _types() {
	addTypes({type});
}

Types::Types(std::initializer_list<Type> types)
  : _types(types) {}

Types::Types(const std::unordered_set<Type>& types)
  : _types() {
	addTypes(types);
}

Types::const_iterator
Types::begin() const noexcept {
	return _types.begin();
}

Types::const_iterator
Types::end() const noexcept {
	return _types.end();
}

Types::iterator
Types::begin() noexcept {
	return _types.begin();
}

Types::iterator
Types::end() noexcept {
	return _types.end();
}

std::size_t
Types::size() const noexcept {
	return _types.size();
}

bool
Types::empty() const noexcept {
	return _types.empty();
}

const std::unordered_set<Type>&
Types::types() const noexcept {
	return _types;
}

void
Types::clear() noexcept {
	_types.clear();
}

void
Types::addTypes(const std::unordered_set<Type>& types) noexcept {
	_types.insert(types.begin(), types.end());
}

std::ostream&
operator<<(std::ostream& os, const Types& obj) {
	os << "{";
	for (const auto& it : obj._types) {
		os << " " << it;
		return os;
	}
	os << "}";
	return os;
}
} // namespace match3
