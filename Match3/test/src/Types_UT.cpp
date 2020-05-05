#include <catch2/catch.hpp>

#include <Match3/Types.hpp>
using match3::Type;
using match3::Types;

TEST_CASE("Type Arithmetic", "[Type]") {
	SECTION("Any/None arithmetic") {
		REQUIRE(Type::Any == Type::Any);
		REQUIRE(Type::None == Type::None);
		REQUIRE(Type::Any != Type::None);
	}
	SECTION("name arithmetic") {
		REQUIRE(Type("a") == Type("a"));
		REQUIRE(Type("a") != Type("b"));
		REQUIRE(Type::Any == Type("a"));
		REQUIRE(Type::None != Type("a"));
	}
}

TEST_CASE("Types Creation", "[Types]") {
	SECTION("Default empty ctor") {
		WHEN("using default ctor") {
			Types types;
			THEN("List must be empty") { REQUIRE(types.size() == 0); }
		}
	}

	SECTION("One Type ctor") {
		WHEN("using Ctor = {{\"name\"}}") {
			// one brace for Type initializer list
			// one brace for Types initializer list.
			Types types = {{"a"}};
			THEN("List size must increase accordingly") {
				REQUIRE(types.size() == 1);
				REQUIRE(*types.types().begin() == Type("a"));
			}
		}
		WHEN("using Ctor = {Type}") {
			Types types = {{"a"}};
			THEN("List size must increase accordingly") {
				REQUIRE(types.size() == 1);
				REQUIRE(*types.types().begin() == Type("a"));
			}
		}
		WHEN("using Ctor({Type})") {
			Types types({Type("a")});
			THEN("List size must increase accordingly") {
				REQUIRE(types.size() == 1);
				REQUIRE(*types.types().begin() == Type("a"));
			}
		}
	}

	SECTION("Several Type ctor") {
		WHEN("using Ctor = {{Type, Type}}") {
			// one brace for Type initializer list
			// one brace for Unordered_set initializer list
			// one brace for Types initializer list.
			Types types = {{{"a"}, Type("b")}};
			THEN("List size must increase accordingly") {
				REQUIRE(types.size() == 2);
				REQUIRE(types.types().count(Type("a")));
				REQUIRE(types.types().count({"b"}));
			}
		}
		WHEN("using Ctor({Type,Type})") {
			Types types({{"a"}, Type("b")});
			THEN("List size must increase accordingly") {
				REQUIRE(types.size() == 2);
				REQUIRE(types.types().count({"a"}));
				REQUIRE(types.types().count({"b"}));
			}
		}
	}
}

TEST_CASE("Types Management", "[Types]") {
	GIVEN("A Types containers") {
		Types types;
		REQUIRE(types.size() == 0);

		WHEN("Adding a type") {
			REQUIRE_NOTHROW(types.addTypes({Type("a")}));
			THEN("size must increase") { REQUIRE(types.size() == 1); }
			AND_WHEN("Adding the same type") {
				REQUIRE_NOTHROW(types.addTypes({Type("a")}));
				THEN("size must remains the same") { REQUIRE(types.size() == 1); }
			}

			WHEN("adding a new type") {
				REQUIRE_NOTHROW(types.addTypes({{"b"}}));
				THEN("size must increase") { REQUIRE(types.size() == 2); }
			}

			WHEN("adding a several types") {
				REQUIRE_NOTHROW(types.addTypes({{"b"}, Type("c"), Type("d")}));
				THEN("size must increase accordingly") { REQUIRE(types.size() == 4); }
				AND_WHEN("adding a several types, whose certains are already present") {
					REQUIRE_NOTHROW(types.addTypes({Type("d"), Type("e")}));
					THEN("size must increase accordingly") { REQUIRE(types.size() == 5); }
				}
			}
		}
	}
}
