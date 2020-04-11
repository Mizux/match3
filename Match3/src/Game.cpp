//! @file

#include <Match3/Game.hpp>

#include <random>

namespace match3 {
Game::Game(Size size)
  : _score()
  , _types(std::make_shared<Types>())
  , _board(std::make_shared<Board>(_types)) {
	_board->resize(std::move(size));
}

std::size_t
Game::score() const noexcept {
	return _score;
}

ConstTypesPtr
Game::types() const noexcept {
	return _types;
}

ConstBoardPtr
Game::board() const noexcept {
	return _board;
}

const Size&
Game::size() const noexcept {
	return _board->size();
}

void
Game::resize(const Size& size) {
	_score = 0;
	_board->resize(size);
}

void
Game::clear() noexcept {
	_score = 0;
	_board->clear();
}

void
Game::reset() noexcept {
	clear();
	_types->clear();
}

void
Game::setTypes(const Types& types) {
	reset();
	_types->addTypes(types.types());
}

void
Game::fillBoard() {
	clear();
	_board->fill();
}
} // namespace match3
