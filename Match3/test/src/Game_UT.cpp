#include <catch2/catch_all.hpp>

#include <Match3/Game.hpp>

namespace match3 {

TEST_CASE("Game creation", "[Game]") {
	SECTION("Default constructor") {
		Game game;
		REQUIRE(game.types()->size() == 0);
		REQUIRE(game.size() == Size({0, 0}));
		REQUIRE(game.score() == 0);
		game.reset();
		REQUIRE(game.types()->size() == 0);
		REQUIRE(game.size() == Size({0, 0}));
		REQUIRE(game.score() == 0);

		WHEN("game board is resized to {8,6}") {
			REQUIRE_NOTHROW(game.resize({8, 6}));
			REQUIRE(game.size() == Size({8, 6}));
			WHEN("fill game board...") {
				REQUIRE(game.types()->size() == 0);
				REQUIRE_THROWS(game.fillBoard());
				REQUIRE_NOTHROW(game.setTypes(Types({{"a"}, {"b"}, {"c"}})));
				REQUIRE_NOTHROW(game.fillBoard());
			}
		}
	}
}
} // namespace match3
