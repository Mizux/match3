//! @file
#pragma once

#include "Type.hpp"
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>

namespace match3 {
class Types;
//! @brief Shared pointer of Types.
using TypesPtr = std::shared_ptr<Types>;
//! @brief Shared pointer of const Types.
using ConstTypesPtr = std::shared_ptr<const Types>;
//! @brief Weak pointer of Types.
using TypesWkPtr = std::weak_ptr<Types>;
//! @brief Weak pointer of const Types.
using ConstTypesWkPtr = std::weak_ptr<const Types>;

//! @brief Store item Type.
class Types {
	public:
	//! @brief Constructs an empty object.
	Types() = default;
	//! @brief Converts a Type into a Types object.
	//! @param[in] type The object to convert.
	Types(const Type& type);
	//! @brief Converts a list of Type into a Types object.
	//! @param[in] types The objects to convert.
	Types(std::initializer_list<Type> types);
	//! @brief Converts a set of Type into a Types object.
	//! @param[in] types The objects to convert.
	Types(const std::unordered_set<Type>& types);
	//! @brief Destructs the object.
	~Types() = default;

	//! @brief Constructs an object with the copy of the content of other.
	Types(const Types&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Types& operator=(const Types&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Types(Types&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Types& operator=(Types&&) = default;

	//! @brief A random access iterator to @ref Type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::unordered_set<Type>::iterator;
	//! @brief A random access iterator to const @ref Type.
	using const_iterator = typename std::unordered_set<Type>::const_iterator;
	//! @brief Get an iterator at the beginning of the vector.
	//! @returns An iterator pointing to the first element in the vector.
	const_iterator begin() const noexcept;
	//! @brief Get an iterator after the end of the vector.
	//! @returns An iterator pointing after the last element in the vector.
	const_iterator end() const noexcept;
	//! @copydoc begin() const.
	iterator begin() noexcept;
	//! @copydoc end() const.
	iterator end() noexcept;

	//! @brief Get the number of types in the pool.
	//! @note won't count special Type "any" and "none".
	//! @return the number of available Type.
	std::size_t size() const noexcept;
	//! @brief Test if Types contains elements.
	//! @note won't count special Type "any" and "none".
	//! @return true if empty, false otherwise.
	bool empty() const noexcept;

	//! @brief Gets list of all available Type so far.
	//! @return the list of available Type.
	const std::unordered_set<Type>& types() const noexcept;
	//! @brief remove all available type.
	//! @note Type::None and Type::Any will remain.
	void clear() noexcept;
	//! @brief Add a new type to the list of available type.
	//! @param[in] types The new Type to add.
	void addTypes(const std::unordered_set<Type>& types) noexcept;

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Types instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Types& obj);

	protected:
	//! @brief Store list of available Type(s).
	std::unordered_set<Type> _types;
};
} // namespace match3
