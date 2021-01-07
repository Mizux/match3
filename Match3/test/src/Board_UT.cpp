#include <catch2/catch_all.hpp>

#include <Match3/Board.hpp>
#include <Match3/Types.hpp>

namespace match3 {

TEST_CASE("Board creation", "[Board]") {
	SECTION("Default constructor") {
		TypesPtr types = std::make_shared<Types>();
		BoardPtr board = std::make_shared<Board>(types);
		REQUIRE(board->size() == Size({0, 0}));
	}

	SECTION("Constructor with size 3x3") {
		TypesPtr types = std::make_shared<Types>();
		BoardPtr board = std::make_shared<Board>(types);
		REQUIRE_NOTHROW(board->resize({3, 3}));
		REQUIRE(board->size() == Size(3, 3));
		REQUIRE(board->items().size() == 0);
		REQUIRE(board->cells().size() == 9);

		WHEN("Resize to {8, 6}") {
			REQUIRE_NOTHROW(board->resize({8, 6}));
			REQUIRE(board->size() == Size(8, 6));
			REQUIRE(board->items().size() == 0);
			REQUIRE(board->cells().size() == 48);
		}
		WHEN("Fill") {
			REQUIRE_NOTHROW(board->clear());
			REQUIRE(board->items().empty());
			REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
			REQUIRE(types->size() == 3);
			REQUIRE_NOTHROW(board->fill());
			THEN("there must have 9 items") {
				INFO("The Board is: " << *board);
				REQUIRE(board->items().size() == 9);
				for (auto const& it : board->items()) {
					REQUIRE(it->type.get() == Type::Any);
					REQUIRE(it->type.get().name() != Type::None.name());
					REQUIRE(it->type.get().name() != Type::Any.name());
				}
				AND_WHEN("board is clear") {
					REQUIRE_NOTHROW(board->clear());
					REQUIRE(board->items().empty());
				}
			}
		}
	}
}

TEST_CASE("Board getter API", "[Board]") {
	TypesPtr types = std::make_shared<Types>();
	REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
	BoardPtr board = std::make_shared<Board>(types);
	REQUIRE_NOTHROW(board->resize({3, 3}));
	Position pos = {1, 2};
	ItemPtr item = std::make_shared<Item>(Type("a"), pos);
	REQUIRE_NOTHROW(board->addItem(item));

	SECTION("Getter for const Board") {
		ConstBoardPtr constBoard = board;
		REQUIRE(constBoard->cells().size() == 9);
		REQUIRE(constBoard->items().size() == 1);
		REQUIRE(constBoard->item(pos) == item);
		REQUIRE(constBoard->item(Position(8, 8)) == nullptr);
		REQUIRE(constBoard->cell(pos) == board->cell(pos));
		REQUIRE(constBoard->cell(Position(8, 8)) == nullptr);
	}

	SECTION("Getter for Board") {
		ConstBoardPtr constBoard = board;
		REQUIRE(board->cells().size() == 9);
		REQUIRE(board->items().size() == 1);
		REQUIRE(board->item(pos) == item);
		REQUIRE(board->item(Position(8, 8)) == nullptr);
		REQUIRE(board->cell(pos) != nullptr);
		REQUIRE(board->cell(Position(8, 8)) == nullptr);
	}
}

TEST_CASE("Adding Item(s)", "[Board]") {
	TypesPtr types = std::make_shared<Types>();
	REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
	BoardPtr board = std::make_shared<Board>(types);
	REQUIRE_NOTHROW(board->resize({3, 3}));

	SECTION("Adding one item in empty cell") {
		REQUIRE_NOTHROW(board->clear());
		ItemPtr item = std::make_shared<Item>(Type("a"), Position(1, 2));
		REQUIRE(item->board.get().lock() == nullptr);
		REQUIRE_NOTHROW(board->addItem(item));
		REQUIRE(item == board->item({1, 2}));
		REQUIRE(item->board.get().lock() == board);
	}
	SECTION("Adding one item in non empty cell") {
		REQUIRE_NOTHROW(board->clear());
		Position pos(1, 2);
		ItemPtr itemA = std::make_shared<Item>(Type("a"), pos);
		REQUIRE_NOTHROW(board->addItem(itemA));
		REQUIRE(itemA->board.get().lock() == board);
		ItemPtr itemB = std::make_shared<Item>(Type("b"), pos);
		REQUIRE(itemA != itemB);
		REQUIRE_THROWS_AS(board->addItem(itemB), std::runtime_error);
		REQUIRE(itemA == board->item(pos));
		REQUIRE(itemB->board.get().lock() == nullptr);
	}
}

TEST_CASE("Removing Item(s)", "[Board]") {
	TypesPtr types = std::make_shared<Types>();
	REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
	BoardPtr board = std::make_shared<Board>(types);
	REQUIRE_NOTHROW(board->resize({3, 3}));

	SECTION("Removing one item in non empty cell") {
		REQUIRE_NOTHROW(board->clear());
		Position pos(1, 2);
		ItemPtr itemA = std::make_shared<Item>(Type("a"), pos);
		REQUIRE_NOTHROW(board->addItem(itemA));
		REQUIRE(board->items().size() == 1);
		THEN("board return item, and remove it from its internal list") {
			ItemPtr item;
			REQUIRE_NOTHROW(item = board->removeItem(pos));
			REQUIRE(item == itemA);
			REQUIRE(board->items().size() == 0);
			REQUIRE(board->removeItem(pos) == nullptr);
		}
	}
	SECTION("Removing severals item in non empty cells") {
		REQUIRE_NOTHROW(board->clear());
		Position posA(1, 2);
		ItemPtr itemA = std::make_shared<Item>(Type("a"), posA);
		REQUIRE_NOTHROW(board->addItem(itemA));
		Position posB(2, 2);
		ItemPtr itemB = std::make_shared<Item>(Type("b"), posB);
		REQUIRE_NOTHROW(board->addItem(itemB));
		REQUIRE(board->items().size() == 2);
		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->removeItems({posA, posB}));
		REQUIRE(items.size() == 2);
		REQUIRE(board->items().size() == 0);
	}

	SECTION("Removing item in empty cell") {
		REQUIRE_NOTHROW(board->clear());
		REQUIRE(board->removeItem(ConstItemPtr()) == nullptr);
		REQUIRE(board->removeItem(Position(1, 2)) == nullptr);
	}
	SECTION("Removing severals items in empty cell") {
		REQUIRE_NOTHROW(board->clear());
		Position posA(1, 2);
		Position posB(2, 2);
		std::vector<ItemPtr> noItems;
		REQUIRE_NOTHROW(noItems = board->removeItems({posA, posB}));
		REQUIRE(noItems.empty());

		ItemPtr itemA = std::make_shared<Item>(Type("a"), posA);
		REQUIRE_NOTHROW(board->addItem(itemA));
		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->removeItems({posA, posB}));
		REQUIRE(items.size() == 1);
		REQUIRE(board->items().empty());

		REQUIRE_NOTHROW(board->addItem(itemA));
		ItemPtr itemB = std::make_shared<Item>(Type("b"), posB);
		REQUIRE_NOTHROW(board->addItem(itemB));
		REQUIRE_NOTHROW(items = board->removeItems({itemA, itemB}));
		REQUIRE(items.size() == 2);
		REQUIRE(board->items().empty());
	}
}

SCENARIO("Matching", "[Board]") {
	TypesPtr types = std::make_shared<Types>();
	REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
	BoardPtr board = std::make_shared<Board>(types);
	REQUIRE_NOTHROW(board->resize({3, 3}));

	SECTION("one item -> no match") {
		REQUIRE_NOTHROW(board->clear());
		Position posA = {1, 2};
		REQUIRE(board->hasMatch(posA) == false);
		ItemPtr itemA = std::make_shared<Item>(Type("a"), posA);
		REQUIRE(board->hasMatch(itemA) == false);
		REQUIRE_NOTHROW(board->addItem(itemA));
		REQUIRE(board->items().size() == 1);
		REQUIRE(board->hasMatch(itemA) == false);
		REQUIRE(board->hasMatch(posA) == false);

		REQUIRE(board->hasMatch() == false);
		REQUIRE(board->getMatches().empty());
		REQUIRE(board->items().size() == 1);
	}
	SECTION("three items -> horizontal match") {
		REQUIRE_NOTHROW(board->clear());
		Position posA = {1, 0};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posA)));
		Position posB = {1, 1};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posB)));
		Position posC = {1, 2};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posC)));
		REQUIRE(board->items().size() == 3);
		REQUIRE(board->hasMatch() == true);
		REQUIRE(board->getMatches().size() == 3);

		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->findandRemoveMatches());
		REQUIRE(items.size() == 3);
		REQUIRE(board->items().empty());
	}
	SECTION("three items -> vertical match") {
		REQUIRE_NOTHROW(board->clear());
		Position posA = {0, 1};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posA)));
		Position posB = {1, 1};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posB)));
		Position posC = {2, 1};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posC)));
		REQUIRE(board->items().size() == 3);
		REQUIRE(board->hasMatch() == true);
		REQUIRE(board->getMatches().size() == 3);

		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->findandRemoveMatches());
		REQUIRE(items.size() == 3);
		REQUIRE(board->items().empty());
	}
}

SCENARIO("Fall", "[Board]") {
	TypesPtr types = std::make_shared<Types>();
	REQUIRE_NOTHROW(types->addTypes({{"a"}, {"b"}, {"c"}}));
	BoardPtr board = std::make_shared<Board>(types);
	REQUIRE_NOTHROW(board->resize({3, 4}));

	SECTION("one item at bottom") {
		REQUIRE_NOTHROW(board->clear());
		Position posA = {0, 0};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posA)));

		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->iterate());
		REQUIRE(items.empty());

		using Gravity = Board::Gravity;
		for (const auto& it : {Gravity::Up, Gravity::Left, Gravity::Right, Gravity::None}) {
			REQUIRE_NOTHROW(board->setGravity(it));
			REQUIRE_THROWS(items = board->iterate());
		}
	}

	SECTION("one item at top") {
		REQUIRE_NOTHROW(board->clear());
		REQUIRE_NOTHROW(board->setGravity(Board::Gravity::Down));
		REQUIRE(board->gravity() == Board::Gravity::Down);
		Position posA = {0, 2};
		REQUIRE_NOTHROW(board->addItem(std::make_shared<Item>(Type("a"), posA)));
		REQUIRE(board->items().size() == 1);

		std::vector<ItemPtr> items;
		REQUIRE_NOTHROW(items = board->iterate());
		REQUIRE(items.size() == 1);
		REQUIRE(items.front()->position.get() == Position(0, 1));
		REQUIRE_NOTHROW(items = board->iterate());
		REQUIRE(items.size() == 1);
		REQUIRE(items.front()->position.get() == Position(0, 0));
		REQUIRE_NOTHROW(items = board->iterate());
		REQUIRE(items.empty());
	}
}
} // namespace match3
