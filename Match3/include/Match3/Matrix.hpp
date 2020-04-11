//! @file
#pragma once

#include "Position.hpp"
#include "Size.hpp"
#include <array>
#include <ostream>
#include <stdexcept>
#include <vector>

namespace match3 {

//! @brief Template to generate fixed size matrix.
//! @details Elements are stored in a single std::array in @b row major.
//! @tparam T Type of each element.
//! @tparam ROWS Number of rows.
//! @tparam COLS Number of columns.
template <typename T, std::size_t ROWS, std::size_t COLS>
struct Matrix_ {
	public:
	//! @brief Type of the elements.
	using value_type = T;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::vector<T>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::vector<T>::const_iterator;
	//! @brief Get an iterator at the beginning of the matrix.
	//! @returns An iterator pointing to the first element in the matrix.
	const_iterator begin() const noexcept { return _data.begin(); }
	//! @brief Get an iterator after the end of the matrix.
	//! @returns An iterator pointing after the last element in the matrix.
	const_iterator end() const noexcept { return _data.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _data.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _data.end(); }

	//! @brief Get number of columns in the matrix.
	//! @return The number of columns.
	inline static std::size_t cols() noexcept { return COLS; }
	//! @brief Get number of rows in the matrix.
	//! @return The number of rows.
	inline static std::size_t rows() noexcept { return ROWS; }
	//! @brief Get the Size the matrix.
	//! @return The size of the matrix, x() will correspond to columns and y() to
	//! rows.
	inline static Size size() noexcept { return Size(COLS, ROWS); }

	//! @brief Proxy class to access a single row matrix.
	class Row {
		//! @brief Need access to parent Matrix whose Row belongs to.
		friend struct Matrix_<T, ROWS, COLS>;

		public:
		/*! @brief Get an elements in the row.
		 * @param[in] col Position of the element requested.
		 * @return Reference on the requested element.*/
		const T& operator[](std::size_t col) const {
			return _parent._data[_row * ROWS + col];
		}
		//! @copydoc operator[](std::size_t) const.
		T& operator[](std::size_t col) { return _parent._data[_row * ROWS + col]; }
		/*! @brief Get an elements in the row.
		 * @param[in] col Position of the element requested.
		 * @throw std::out_of_range if column index is not in the matrix.
		 * @return Reference on the requested element.*/
		const T& at(std::size_t col) const {
			if (col >= COLS) throw std::out_of_range("Column index is out of the range.");
			return _parent._data.at(_row * ROWS + col);
		}
		//! @copydoc operator[](std::size_t) const.
		T& at(std::size_t col) {
			if (col >= COLS) throw std::out_of_range("Column index is out of the range.");
			return _parent._data.at(_row * ROWS + col);
		}

		private:
		/*! @brief Base constructor.
		 * @param[in] parent @ref Matrix_ whose Row belongs to.
		 * @param[in] row Position of this row in the matrix*/
		Row(Matrix_<T, ROWS, COLS>& parent, std::size_t row)
		  : _parent(parent)
		  , _row(row) {}

		//! @brief Parent @ref Matrix_.
		Matrix_<T, ROWS, COLS>& _parent;
		//! @brief Row position in the parent matrix.
		std::size_t _row;
	};

	/*! @brief Get access to a single row.
	 * @details For a bound-checked version, look at @ref at(std::size_t) const
	 * method.
	 * @param[in] row Row index requested.
	 * @return @ref Row object to access the requested row.*/
	const Row operator[](std::size_t row) const noexcept { return Row(*this, row); }
	//! @copydoc operator[](std::size_t) const.
	Row operator[](std::size_t row) noexcept { return Row(*this, row); }

	/*! @brief Get access to a single row.
	 * @param[in] row Row index requested.
	 * @throw std::out_of_range if row index is not in the matrix.
	 * @return @ref Row object to access the requested row.*/
	const Row at(std::size_t row) const {
		if (row >= ROWS) throw std::out_of_range("Row index is out of the range.");
		return Row(*this, row);
	}
	//! @copydoc at(std::size_t) const.
	Row at(std::size_t row) {
		if (row >= ROWS) throw std::out_of_range("Row index is out of the range.");
		return Row(*this, row);
	}

	protected:
	//! @brief Store all matrix elements in a contiguous array.
	std::array<T, ROWS * COLS> _data;
};

///////////////////////
//  MATRIX SIZE 2x2  //
///////////////////////

//! @brief Matrix of fixed size 2x2
//! @tparam T Type of each element.
template <typename T>
struct Matrix2 : public Matrix_<T, 2, 2> {};

//! @brief Matrix of int of fixed size 2x2
using Matrix2i = Matrix2<int>;
//! @brief Matrix of float of fixed size 2x2
using Matrix2f = Matrix2<float>;
//! @brief Matrix of double of fixed size 2x2
using Matrix2d = Matrix2<double>;

///////////////////////
//  MATRIX SIZE 3x3  //
///////////////////////

//! @brief Matrix of fixed size 3x3
//! @tparam T Type of each element.
template <typename T>
struct Matrix3 : public Matrix_<T, 3, 3> {};

//! @brief Matrix of int of fixed size 3x3
using Matrix3i = Matrix3<int>;
//! @brief Matrix of float of fixed size 3x3
using Matrix3f = Matrix3<float>;
//! @brief Matrix of double of fixed size 3x3
using Matrix3d = Matrix3<double>;

///////////////////////
//  MATRIX SIZE 4x4  //
///////////////////////

//! @brief Matrix of fixed size 4x4
//! @tparam T Type of each element.
template <typename T>
struct Matrix4 : public Matrix_<T, 4, 4> {};

//! @brief Matrix of int of fixed size 4x4
using Matrix4i = Matrix4<int>;
//! @brief Matrix of float of fixed size 4x4
using Matrix4f = Matrix4<float>;
//! @brief Matrix of double of fixed size 4x4
using Matrix4d = Matrix4<double>;

//////////////////////////////
//  MATRIX OF DYNAMIC SIZE  //
//////////////////////////////

//! @brief Template to generate resizable matrix.
//! @details Elements are stored in a single std::vector in @b row major.
//! @tparam T Type of each element.
template <typename T>
struct Matrix {
	//! @brief Type of the elements.
	using value_type = T;
	//! @brief A random access iterator to @ref value_type.
	//! @note Convertible to const_iterator.
	using iterator = typename std::vector<T>::iterator;
	//! @brief A random access iterator to const @ref value_type.
	using const_iterator = typename std::vector<T>::const_iterator;
	//! @brief Get an iterator at the beginning of the matrix.
	//! @returns An iterator pointing to the first element in the matrix.
	const_iterator begin() const noexcept { return _data.begin(); }
	//! @brief Get an iterator after the end of the matrix.
	//! @returns An iterator pointing after the last element in the matrix.
	const_iterator end() const noexcept { return _data.end(); }
	//! @copydoc begin() const.
	iterator begin() noexcept { return _data.begin(); }
	//! @copydoc end() const.
	iterator end() noexcept { return _data.end(); }

	//! @brief Get number of columns in the matrix.
	//! @return The number of columns.
	inline std::size_t cols() const noexcept { return _size.x(); }
	//! @brief Get number of rows in the matrix.
	//! @return The number of rows.
	inline std::size_t rows() const noexcept { return _size.y(); }
	//! @brief Get the Size the matrix.
	//! @return The size of the matrix, x() will correspond to columns and y() to
	//! rows.
	inline Size size() const noexcept { return _size; }

	/*! @brief Resize matrix to the requested size.
	 * @param[in] size Size requested.*/
	void resize(Size size) noexcept {
		_size = std::move(size);
		_data = std::move(std::vector<value_type>(_size.x() * _size.y()));
	}

	//! @brief Default constructor.
	//!  @param[in] size Initial container size (i.e., the number of elements in the
	//!  container at construction).
	Matrix(Size size = {0, 0})
	  : _size(std::move(size))
	  , _data(_size.x() * _size.y()) {}
	//! @brief Default constructor.
	//!  @param[in] rows Initial number of rows in the container at construction.
	//!  @param[in] cols Initial number of columns in the container at construction.
	Matrix(std::size_t rows, std::size_t cols)
	  : _size({cols, rows})
	  , _data(_size.x() * _size.y()) {}
	//! @brief Destructs the object.
	~Matrix() = default;

	//! @brief Constructs an object with the copy of the content of other.
	Matrix(const Matrix&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Matrix& operator=(const Matrix&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Matrix(Matrix&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Matrix& operator=(Matrix&&) = default;

	//! @brief Proxy class to access a single row matrix.
	class Row {
		//! @brief Need access to parent Matrix whose Row belongs to.
		friend struct Matrix<T>;

		public:
		/*! @brief Get an elements in the row.
		 * @param[in] col Position of the element requested.
		 * @return Reference on the requested element.*/
		const T& operator[](std::size_t col) const {
			return _parent._data[_row * _parent.cols() + col];
		}
		//! @copydoc operator[](std::size_t) const.
		T& operator[](std::size_t col) {
			return _parent._data[_row * _parent.cols() + col];
		}
		/*! @brief Get an elements in the row.
		 * @param[in] col Position of the element requested.
		 * @throw std::out_of_range if column index is not in the matrix.
		 * @return Reference on the requested element.*/
		const T& at(std::size_t col) const {
			if (col >= _parent.cols())
				throw std::out_of_range("Column index is out of the range.");
			return _parent._data.at(_row * _parent.cols() + col);
		}
		//! @copydoc operator[](std::size_t) const.
		T& at(std::size_t col) {
			if (col >= _parent.cols())
				throw std::out_of_range("Column index is out of the range.");
			return _parent._data.at(_row * _parent.cols() + col);
		}

		private:
		/*! @brief Base constructor.
		 * @param[in] parent @ref Matrix_ whose Row belongs to.
		 * @param[in] row Position of this row in the matrix*/
		Row(Matrix<T>& parent, std::size_t row)
		  : _parent(parent)
		  , _row(row) {}

		//! @brief Parent Matrix.
		Matrix<T>& _parent;
		//! @brief Row position in the parent matrix.
		std::size_t _row;
	};

	/*! @brief Get access to a single row.
	 * @details For a bound-checked version, look at @ref Matrix::at(std::size_t)
	 * const methods.
	 * @param[in] row Row index requested.
	 * @return @ref Row object to access the requested row.*/
	const Row operator[](std::size_t row) const noexcept { return Row(*this, row); }
	//! @copydoc operator[](std::size_t) const.
	Row operator[](std::size_t row) noexcept { return Row(*this, row); }

	/*! @brief Get access to a single row.
	 * @param[in] row Row index requested.
	 * @throw std::out_of_range if row index is not in the matrix.
	 * @return @ref Row object to access the requested row.*/
	const Row at(std::size_t row) const {
		if (row >= _size.y()) throw std::out_of_range("Row index is out of the range.");
		return Row(*this, row);
	}
	//! @copydoc at(std::size_t) const.
	Row at(std::size_t row) {
		if (row >= _size.y()) throw std::out_of_range("Row index is out of the range.");
		return Row(*this, row);
	}

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Matrix instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Matrix& obj) {
		os << "{";
		for (std::size_t j = 0; j < obj.rows(); ++j) {
			if (j != 0) os << ", ";
			os << "{";
			for (std::size_t i = 0; i < obj.cols(); ++i) {
				if (i != 0) os << ", ";
				os << obj._data[j][i];
			}
		}
		os << "}";
		return os;
	}

	protected:
	//! @brief Size of the Matrix.
	Size _size;
	//! @brief Stores matrix elements.
	std::vector<T> _data;
};
} // namespace match3

namespace std {

//! @brief custom specialization of std::hash for @ref match3::Matrix_.
template <typename T, std::size_t ROWS, std::size_t COLS>
struct hash<match3::Matrix_<T, ROWS, COLS>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Matrix_ type.
	//! @param[in] mat The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Matrix_<T, ROWS, COLS>& mat) const {
		if (mat.size() == match3::Size({0, 0})) return 0;
		std::size_t out(std::hash<T>()(mat[0]));
		for (size_t i = 1; i < mat.cols() && i < mat.rows(); ++i) {
			out ^= (std::hash<T>(mat[i][i]) << i);
		}
		return out;
	}
};

//! @brief custom specialization of std::hash for @ref match3::Matrix.
template <typename T>
struct hash<match3::Matrix<T>> {
	//! @brief Hash function (i.e. operator()) for @ref match3::Matrix type.
	//! @param[in] mat The object to be hashed.
	//! @return a std::size_t representing the hash value.
	std::size_t operator()(const match3::Matrix<T>& mat) const {
		if (mat.size() == match3::Size({0, 0})) return 0;
		std::size_t out(std::hash<T>()(mat[0]));
		for (size_t i = 1; i < mat.size(); ++i) {
			out ^= (std::hash<T>(mat[i]) << i);
		}
		return out;
	}
};
} // namespace std
