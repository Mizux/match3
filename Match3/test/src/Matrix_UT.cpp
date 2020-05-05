#include <catch2/catch.hpp>

#include <Match3/Matrix.hpp>
using match3::Matrix;
using match3::Matrix_;
using match3::Size;

SCENARIO("Matrix_ Creation", "[matrix_]") {
	REQUIRE(Size({5, 3}).x() == 5);
	REQUIRE(Size({5, 3}).y() == 3);

	WHEN("creating a matrix 3x5") {
		Matrix_<int, 3, 5> mat;
		THEN("size must be 5 columns and 3 rows") {
			REQUIRE(mat.size() == Size({5, 3}));
			REQUIRE(mat.cols() == 5);
			REQUIRE(mat.rows() == 3);
		}
		THEN("All elements must be zero initialized") {
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 5; ++j) {
					mat[i][j] = 0;
					REQUIRE(mat.at(i).at(j) == 0);
				}
			}
		}
	}
}

SCENARIO("Matrix Creation", "[matrix]") {
	WHEN("creating a matrix") {
		Matrix<int> mat;
		THEN("size must be 0x0") {
			REQUIRE(mat.size() == Size({0, 0}));
			REQUIRE(mat.cols() == 0);
			REQUIRE(mat.rows() == 0);
		}
	}

	GIVEN("a 3x3 matrix") {
		Matrix<int> mat(Size({3, 3}));
		REQUIRE(mat.size() == Size({3, 3}));
		REQUIRE(mat.cols() == 3);
		REQUIRE(mat.rows() == 3);
		// init to zero
		WHEN("Matrix is initialized to zero") {
			int count = 0;
			for (auto& it : mat) {
				it = 0;
				count++;
			}
			REQUIRE(count == 9);
			for (auto const& it : mat) {
				REQUIRE(it == 0);
			}
		}
		mat[0][0] = 2;
		WHEN("size is set to 8x6") {
			mat.resize(Size({8, 6}));
			THEN("size change and all value are reset to default initializer") {
				REQUIRE(mat.size() == Size({8, 6}));
				REQUIRE(mat.cols() == 8);
				REQUIRE(mat.rows() == 6);
				for (auto const& it : mat) {
					REQUIRE(it == 0);
				}
			}
		}
	}
}

SCENARIO("Matrix Accessor", "[matrix]") {
	GIVEN("a matrix 7x3") {
		Matrix<int> mat(3, 7);
		REQUIRE(mat.size() == Size({7, 3}));
		REQUIRE(mat.cols() == 7);
		REQUIRE(mat.rows() == 3);
		THEN("access to out of the range must throw") {
			REQUIRE_THROWS_AS(mat.at(3).at(0), std::out_of_range);
			REQUIRE_THROWS_AS(mat.at(0).at(7), std::out_of_range);
		}
	}
}
