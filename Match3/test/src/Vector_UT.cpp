#include <catch2/catch.hpp>

#include <Match3/Vector.hpp>

namespace match3 {

TEST_CASE("class Vector", "[vector]") {
	SECTION("Ctor") {
		Vector<int> vec;
		REQUIRE(vec.size() == 0);
	}

	GIVEN("a vector 3") {
		Vector<int> vec(3);
		REQUIRE(vec.size() == 3);
		for (auto const& it : vec) {
			REQUIRE(it == 0);
		}
		vec.at(1) = 2;
		REQUIRE(vec[1] == 2);
		WHEN("size is set to 8") {
			vec.resize(8);
			THEN("size change and all value are reset to default initializer") {
				REQUIRE(vec.size() == 8);
				for (auto const& it : vec) {
					REQUIRE(it == 0);
				}
			}
			THEN("access to out of the range must throw") {
				REQUIRE_THROWS_AS(vec.at(8), std::out_of_range);
			}
		}
	}
}

TEST_CASE("class Vector_", "[vector]") {
	SECTION("default Ctor") {
		Vector_<int, 0> vec;
		REQUIRE(vec.size() == 0);
	}

	SECTION("getter") {
		Vector_<int, 3> vec;
		REQUIRE(vec.size() == 3);
		for (auto& it : vec) {
			it = 0;
			REQUIRE(it == 0);
		}
		vec.at(1) = 2;
		REQUIRE(vec[1] == 2);
		REQUIRE_THROWS_AS(vec.at(7), std::out_of_range);
	}

	SECTION("arithmetic") {
		Vector_<int, 2> a;
		REQUIRE(a.size() == 2);
		a[0] = 1;
		a[1] = 2;
		REQUIRE(a == Vector2i(1, 2));
		Vector_<int, 2> b;
		REQUIRE(b.size() == 2);
		b[0] = 3;
		b[1] = 4;
		REQUIRE(b == Vector2i(3, 4));
		REQUIRE(a != b);
		SECTION("addition") {
			REQUIRE((a + b) == Vector2i(4, 6));
			REQUIRE(a == Vector2i(1, 2));
			REQUIRE(b == Vector2i(3, 4));
		}
		SECTION("substraction") {
			REQUIRE((b - a) == Vector2i(2, 2));
			REQUIRE(a == Vector2i(1, 2));
			REQUIRE(b == Vector2i(3, 4));
		}
	}
}

TEST_CASE("class Vector2", "[vector]") {
	SECTION("default Ctor") {
		Vector2<int> vec2;
		REQUIRE(vec2.size() == 2);
	}

	SECTION("getter") {
		Vector2i vec;
		REQUIRE(vec.size() == 2);
		for (auto& it : vec) {
			it = 0;
			REQUIRE(it == 0);
		}
		vec.at(1) = 2;
		REQUIRE(vec[1] == 2);
		REQUIRE_THROWS_AS(vec.at(7), std::out_of_range);
	}

	SECTION("arithmetic") {
		Vector2i a(1, 2);
		REQUIRE(a == Vector2i(1, 2));
		Vector2i b(3, 4);
		REQUIRE(b == Vector2i(3, 4));
		REQUIRE(a != b);
		SECTION("addition") {
			REQUIRE(a + b == Vector2i(4, 6));
			REQUIRE(a == Vector2i(1, 2));
			REQUIRE(b == Vector2i(3, 4));
		}
		SECTION("operator +=") {
			Vector2i a(1, 2);
			a += Vector2i(3, 7);
			REQUIRE(a == Vector2i(4, 9));
		}

		SECTION("substraction") {
			REQUIRE(b - a == Vector2i(2, 2));
			REQUIRE(a == Vector2i(1, 2));
			REQUIRE(b == Vector2i(3, 4));
		}
	}
}
} // namespace match3
