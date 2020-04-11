//! @file
#pragma once

#include <ostream>
#include <string>
#include <unordered_set>

namespace match3 {
//! @brief Store item type.
class Type {
	public:
	//! @brief Default constructor.
	//! @param[in] name The Type name.
	Type(std::string name);
	//! @brief Destructs the object.
	~Type() = default;

	//! @brief Represent an empty Type.
	static const Type None;
	//! @brief Represent a wildchar Type which could match any Type,
	//! except @ref Type::None
	static const Type Any;

	//! @brief Constructs an object with the copy of the content of other.
	Type(const Type&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Type& operator=(const Type&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Type(Type&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Type& operator=(Type&&) = default;

	//! @brief Checks if the contents of this instance and rhs are equal.
	//! @param[in] rhs The second instance to compare with.
	//! @return true if equal, false otherwise.
	bool operator==(const Type& rhs) const noexcept;
	//! @brief Checks if the contents of this instance and rhs are differents.
	//! @param[in] rhs The second instance to compare with.
	//! @return true if not equal, false otherwise.
	bool operator!=(const Type& rhs) const noexcept;

	//! @brief Get Type name.
	//! @return name of the type.
	const std::string& name() const noexcept;

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Cell instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Type& obj) {
		os << obj.name();
		return os;
	}

	private:
	//! @brief Store name of the type.
	std::string _name;
};
} // namespace match3

namespace std {
//! @brief custom specialization of std::hash for @ref match3::Type.
template <>
struct hash<match3::Type> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Type type.
	//! @param[in] type The object to be hashed.
	//! @return a std::size_t representing the hash value.
	size_t operator()(const match3::Type& type) const {
		return std::hash<string>()(type.name());
	}
};
} // namespace std
