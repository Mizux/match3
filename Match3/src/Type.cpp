//! @file
#include <Match3/Type.hpp>

#include <exception>
#include <string>

namespace match3 {

const Type Type::None = Type("");
const Type Type::Any  = Type("*");

Type::Type(std::string name)
  : _name(std::move(name)) {}

const std::string&
Type::name() const noexcept {
	return _name;
}

bool
Type::operator==(const Type& rhs) const noexcept {
	return ((_name == rhs._name) ||
	        (_name == Type::Any.name() && rhs._name != Type::None.name()) ||
	        (_name != Type::None.name() && rhs._name == Type::Any.name()));
}

bool
Type::operator!=(const Type& rhs) const noexcept {
	return !(*this == rhs);
}
} // namespace match3
