//! @file
#pragma once

#include <array>
#include <ostream>
#include <vector>

namespace match3 {

/////////////////////////
//  VECTOR FIXED SIZE  //
/////////////////////////

//! @brief Vector of fixed size
//! @tparam T Type of each element.
//! @tparam N Size of the vector.
template <typename T, std::size_t N>
struct Vector_ {
	//! @brief Type of the elements.
	using value_type = T;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::array<T, N>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::array<T, N>::const_iterator;
	//! @brief Get an iterator at the beginning of the vector.
	//! @returns An iterator pointing to the first element in the vector.
	const_iterator begin() const noexcept { return _data.begin(); }
	//! @brief Get an iterator after the end of the vector.
	//! @returns An iterator pointing after the last element in the vector.
	const_iterator end() const noexcept { return _data.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _data.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _data.end(); }

	//! @brief Default constructor.
	Vector_() = default;
	//! @brief Destructs the object.
	virtual ~Vector_() = default;

	//! @brief Constructs a Vector_ with the copy of the content of other.
	Vector_(const Vector_&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Vector_& operator=(const Vector_&) = default;
	//! @brief Constructs a Vector_ with the contents of other using move semantics.
	Vector_(Vector_&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Vector_& operator=(Vector_&&) = default;

	//! @brief Get the Size the vector.
	//! @return The size of the vector.
	inline static std::size_t size() noexcept { return N; }

	//! @brief Checks if the contents of this instance and rhs are equal.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator==(const Vector_<T, N>& rhs) const {
		for (std::size_t i = 0; i < N; ++i) {
			if (_data[i] != rhs._data[i]) return false;
		}
		return true;
	}
	//! @brief Checks if the contents of this instance and rhs are differents.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator!=(const Vector_<T, N>& rhs) const { return !(*this == rhs); }

	//! @brief Overload of operator<.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator<(const Vector_<T, N>& rhs) const {
		for (std::size_t i = 0; i < N - 1; ++i) {
			if (_data[i] < rhs._data[i])
				return true;
			else if (_data[i] > rhs._data[i])
				return false;
		}
		return _data.back() < rhs._data.back();
	}

	//! @brief Overload of operator+.
	//! @param[in] rhs Object whose content to add.
	//! @return the sum of both values.
	inline Vector_<T, N> operator+(const Vector_<T, N>& rhs) const {
		Vector_<T, N> res(*this);
		for (std::size_t i = 0; i < N; ++i) {
			res._data[i] += rhs._data[i];
		}
		return res;
	}
	//! @brief Overload of operator+=.
	//! @param[in] rhs Object whose content to add.
	//! @return *this.
	inline Vector_<T, N>& operator+=(const Vector_<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i) {
			_data[i] += rhs._data[i];
		}
		return *this;
	}

	//! @brief Overload of operator-.
	//! @param[in] rhs Object whose content to substract.
	//! @return the difference of both values.
	inline Vector_<T, N> operator-(const Vector_<T, N>& rhs) const {
		Vector_<T, N> res(*this);
		for (std::size_t i = 0; i < N; ++i) {
			res._data[i] -= rhs._data[i];
		}
		return res;
	}
	//! @brief Overload of operator-=.
	//! @param[in] rhs Object whose content to substract.
	//! @return *this.
	inline Vector_<T, N>& operator-=(const Vector_<T, N>& rhs) {
		for (std::size_t i = 0; i < N; ++i) {
			_data[i] -= rhs._data[i];
		}
		return *this;
	}

	/*! @brief Get access to a single element.
	 * @details For a bound-checked version, look at @ref at(std::size_t) const
	 * method.
	 * @param[in] i Component index requested.
	 * @return The requested element.*/
	inline const T& operator[](std::size_t i) const noexcept { return _data[i]; }
	//! @copydoc operator[](std::size_t) const.
	inline T& operator[](std::size_t i) noexcept { return _data[i]; }

	/*! @brief Get access to a single element.
	 * @param[in] i Component index requested.
	 * @throw std::out_of_range if component index is not in the vector.
	 * @return The requested element.*/
	inline const T& at(std::size_t i) const { return _data.at(i); }
	//! @copydoc at(std::size_t) const.
	inline T& at(std::size_t i) { return _data.at(i); }

	protected:
	//! @brief Store all vector elements in a contiguous array.
	std::array<T, N> _data;
};

/////////////////////
//  VECTOR SIZE 2  //
/////////////////////

//! @brief Vector of fixed size 2
template <typename T>
struct Vector2 : public Vector_<T, 2> {
	Vector2()
	  : Vector_<T, 2>() {}
	//! @brief Constructs a Vector2 with the copy of the content of other.
	//! @param[in] vec The vector to copy.
	Vector2(const Vector_<T, 2>& vec)
	  : Vector_<T, 2>(vec) {}
	//! @brief Default constructor
	//! @param[in] x Initial value of the first component.
	//! @param[in] y Initial value of the second component.
	Vector2(T x, T y)
	  : Vector_<T, 2>() {
		this->_data = {{std::move(x), std::move(y)}};
	}
	//! @brief Destructs the object.
	~Vector2() override = default;

	//! @brief Constructs a Vector2 with the copy of the content of other.
	Vector2(const Vector2&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Vector2& operator=(const Vector2&) = default;
	//! @brief Constructs a Vector2 with the contents of other using move semantics.
	Vector2(Vector2&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Vector2& operator=(Vector2&&) = default;

	//! @brief Get value of the X (i.e. index 0) component.
	//! @return value of the component.
	inline const T& x() const noexcept { return this->_data[0]; }
	//! @copydoc x() const
	inline T& x() noexcept { return this->_data[0]; }

	//! @brief Get value of the Y (i.e. index 1) component.
	//! @return value of the component.
	inline const T& y() const noexcept { return this->_data[1]; }
	//! @copydoc y() const
	inline T& y() noexcept { return this->_data[1]; }

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Object to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& obj) {
		os << "{x: " << obj.x() << ", y: " << obj.y() << "}";
		return os;
	}
};

//! @brief Vector of int of fixed size 2
using Vector2i = Vector2<int>;
//! @brief Vector of float of fixed size 2
using Vector2f = Vector2<float>;
//! @brief Vector of double of fixed size 2
using Vector2d = Vector2<double>;

/////////////////////
//  VECTOR SIZE 3  //
/////////////////////

//! @brief Vector of fixed size 3
template <typename T>
struct Vector3 : public Vector_<T, 3> {
	Vector3()
	  : Vector_<T, 3>() {}
	//! @brief Constructs a Vector3 with the copy of the content of other.
	//! @param[in] vec The vector to copy.
	Vector3(const Vector_<T, 3>& vec)
	  : Vector_<T, 3>(vec) {}
	//! @brief Default constructor
	//! @param[in] x Initial value of the first component.
	//! @param[in] y Initial value of the second component.
	//! @param[in] z Initial value of the third component.
	Vector3(T x, T y, T z)
	  : Vector_<T, 3>() {
		this->_data = {std::move(x), std::move(y), std::move(z)};
	}
	//! @brief Destructs the object.
	~Vector3() = default;

	//! @brief Constructs a Vector3 with the copy of the content of other.
	Vector3(const Vector3&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Vector3& operator=(const Vector3&) = default;
	//! @brief Constructs a Vector3 with the contents of other using move semantics.
	Vector3(Vector3&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Vector3& operator=(Vector3&&) = default;

	//! @brief Get value of the X (i.e. index 0) component.
	//! @return value of the component.
	inline T x() const noexcept { return this->_data[0]; }
	//! @copydoc x() const.
	inline T& x() noexcept { return this->_data[0]; }

	//! @brief Get value of the Y (i.e. index 1) component.
	//! @return value of the component.
	inline T y() const noexcept { return this->_data[1]; }
	//! @copydoc y() const.
	inline T& y() noexcept { return this->_data[1]; }

	//! @brief Get value of the Z (i.e. index 2) component.
	//! @return value of the component.
	inline T z() const noexcept { return this->_data[2]; }
	//! @copydoc z() const.
	inline T& z() noexcept { return this->_data[2]; }

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Object to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& obj) {
		os << "{x: " << obj.x() << ", y: " << obj.y() << ", z: " << obj.z() << "}";
		return os;
	}
};

//! @brief Vector of int of fixed size 3
using Vector3i = Vector3<int>;
//! @brief Vector of float of fixed size 3
using Vector3f = Vector3<float>;
//! @brief Vector of double of fixed size 3
using Vector3d = Vector3<double>;

/////////////////////
//  VECTOR SIZE 4  //
/////////////////////

//! @brief Vector of fixed size 4
template <typename T>
struct Vector4 : public Vector_<T, 4> {
	Vector4()
	  : Vector_<T, 4>() {}
	//! @brief Constructs a Vector4 with the copy of the content of other.
	//! @param[in] vec The vector to copy.
	Vector4(const Vector_<T, 4>& vec)
	  : Vector_<T, 4>(vec) {}
	//! @brief Default constructor
	//! @param[in] x Initial value of the first component.
	//! @param[in] y Initial value of the second component.
	//! @param[in] z Initial value of the third component.
	//! @param[in] w Initial value of the fourth component.
	Vector4(T x, T y, T z, T w)
	  : Vector_<T, 4>() {
		this->_data = {std::move(x), std::move(y), std::move(z), std::move(w)};
	}
	//! @brief Destructs the object.
	~Vector4() = default;

	//! @brief Constructs a Vector3 with the copy of the content of other.
	Vector4(const Vector4&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Vector4& operator=(const Vector4&) = default;
	//! @brief Constructs a Vector3 with the contents of other using move semantics.
	Vector4(Vector4&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Vector4& operator=(Vector4&&) = default;

	//! @brief Get value of the X (i.e. index 0) component.
	//! @return value of the component.
	inline const T& x() const noexcept { return this->_data[0]; }
	//! @copydoc x() const
	inline T& x() noexcept { return this->_data[0]; }

	//! @brief Get value of the Y (i.e. index 1) component.
	//! @return value of the component.
	inline const T& y() const noexcept { return this->_data[1]; }
	//! @copydoc y() const
	inline T& y() noexcept { return this->_data[1]; }

	//! @brief Get value of the Z (i.e. index 2) component.
	//! @return value of the component.
	inline const T& z() const noexcept { return this->_data[2]; }
	//! @copydoc z() const
	inline T& z() noexcept { return this->_data[2]; }

	//! @brief Get value of the W (i.e. index 3) component.
	//! @return value of the component.
	inline const T& w() const noexcept { return this->_data[3]; }
	//! @copydoc w() const
	inline T& w() noexcept { return this->_data[3]; }

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Object to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Vector4<T>& obj) {
		os << "{x: " << obj.x() << ", y: " << obj.y() << ", z: " << obj.z()
		   << ", w: " << obj.w() << "}";
		return os;
	}
};

//! @brief Vector of int of fixed size 4
using Vector4i = Vector4<int>;
//! @brief Vector of float of fixed size 4
using Vector4f = Vector4<float>;
//! @brief Vector of double of fixed size 4
using Vector4d = Vector4<double>;

//////////////////////////////
//  VECTOR OF DYNAMIC SIZE  //
//////////////////////////////

//! @brief Vector of dynamic size
template <typename T = int>
struct Vector {
	//! @brief Type of the elements.
	using value_type = T;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::vector<T>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::vector<T>::const_iterator;
	//! @brief Get an iterator at the beginning of the vector.
	//! @returns An iterator pointing to the first element in the vector.
	const_iterator begin() const noexcept { return _data.begin(); }
	//! @brief Get an iterator after the end of the vector.
	//! @returns An iterator pointing after the last element in the vector.
	const_iterator end() const noexcept { return _data.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _data.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _data.end(); }

	//! @brief Default constructor.
	//! @param[in] size Size of the vector.
	Vector(std::size_t size = 0)
	  : _data(std::move(size)) {}
	//! @brief Destructs the object.
	~Vector() = default;

	//! @brief Constructs a Vector with the copy of the content of other.
	Vector(const Vector&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Vector& operator=(const Vector&) = default;
	//! @brief Constructs a Vector with the contents of other using move semantics.
	Vector(Vector&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Vector& operator=(Vector&&) = default;

	//! @brief Get the Size the vector.
	//! @return The size of the vector.
	inline std::size_t size() const noexcept { return _data.size(); }
	//! @brief Resize the vector to the specified one.
	//! @param[in] size The new size requested.
	inline void resize(std::size_t size) {
		_data.clear();
		_data.resize(size);
	}

	//! @brief Checks if the contents of this instance and rhs are equal.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator==(const Vector<T>& rhs) const {
		for (std::size_t i = 0; i < _data.size(); ++i) {
			if (_data[i] != rhs._data[i]) return false;
		}
		return true;
	}
	//! @brief Checks if the contents of this instance and rhs are differents.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator!=(const Vector<T>& rhs) const { return !(*this == rhs); }

	//! @brief Overload of operator<.
	//! @param[in] rhs Vector whose content to compare.
	//! @return true if the corresponding comparison holds, false otherwise.
	inline bool operator<(const Vector<T>& rhs) const {
		for (std::size_t i = 0; i < _data.size() - 1; ++i) {
			if (_data[i] < rhs._data[i])
				return true;
			else if (_data[i] > rhs._data[i])
				return false;
		}
		return _data.back() < rhs._data.back();
	}

	/*! @brief Get access to a single element.
	 * @details For a bound-checked version, look at @ref at(std::size_t) const
	 * method.
	 * @param[in] i Component index requested.
	 * @return The requested element.*/
	inline const T& operator[](std::size_t i) const noexcept { return _data[i]; }
	//! @copydoc operator[](std::size_t) const.
	inline T& operator[](std::size_t i) noexcept { return _data[i]; }

	/*! @brief Get access to a single element.
	 * @param[in] i Component index requested.
	 * @throw std::out_of_range if component index is not in the vector.
	 * @return The requested element.*/
	inline const T& at(std::size_t i) const { return _data.at(i); }
	//! @copydoc at(std::size_t) const.
	inline T& at(std::size_t i) { return _data.at(i); }

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Object to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Vector<T>& obj) {
		os << "{";
		for (std::size_t i = 0; i < obj.size(); ++i) {
			if (i != 0) os << ", ";
			os << std::to_string(i) << ": " << obj[i];
		}
		os << "}";
		return os;
	}

	protected:
	//! @brief Store vector elements in a contiguous array (i.e. std::vector).
	std::vector<T> _data;
};
} // namespace match3

namespace std {

//! @brief custom specialization of std::hash for @ref match3::Vector_.
template <typename T, std::size_t N>
struct hash<match3::Vector_<T, N>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Vector_ type.
	//! @param[in] vec The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Vector_<T, N>& vec) const {
		if (vec.size() == 0) return 0;
		std::size_t out(std::hash<T>()(vec[0]));
		for (size_t i = 1; i < vec.size(); ++i) {
			out ^= (std::hash<T>(vec[i]) << i);
		}
		return out;
	}
};

//! @brief custom specialization of std::hash for @ref match3::Vector2.
template <typename T>
struct hash<match3::Vector2<T>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Vector2 type.
	//! @param[in] vec The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Vector2<T>& vec) const {
		const std::size_t hx(std::hash<T>()(vec.x()));
		const std::size_t hy(std::hash<T>()(vec.y()));
		return hx ^ (hy << 1);
	}
};

//! @brief custom specialization of std::hash for @ref match3::Vector3.
template <typename T>
struct hash<match3::Vector3<T>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Vector3 type.
	//! @param[in] vec The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Vector3<T>& vec) const {
		const std::size_t hx(std::hash<T>()(vec.x()));
		const std::size_t hy(std::hash<T>()(vec.y()));
		const std::size_t hz(std::hash<T>()(vec.z()));
		return hx ^ (hy << 1) ^ (hz << 2);
	}
};

//! @brief custom specialization of std::hash for @ref match3::Vector4.
template <typename T>
struct hash<match3::Vector4<T>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Vector4 type.
	//! @param[in] vec The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Vector4<T>& vec) const {
		const std::size_t hx(std::hash<T>()(vec.x()));
		const std::size_t hy(std::hash<T>()(vec.y()));
		const std::size_t hz(std::hash<T>()(vec.z()));
		const std::size_t hw(std::hash<T>()(vec.w()));
		return hx ^ (hy << 1) ^ (hz << 2) ^ (hw << 3);
	}
};

//! @brief custom specialization of std::hash for @ref match3::Vector.
template <typename T>
struct hash<match3::Vector<T>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Vector type.
	//! @param[in] vec The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Vector<T>& vec) const {
		if (vec.size() == 0) return 0;
		std::size_t out(std::hash<T>()(vec[0]));
		for (size_t i = 1; i < vec.size(); ++i) {
			out ^= (std::hash<T>(vec[i]) << i);
		}
		return out;
	}
};
} // namespace std
