//! @file

#include <Match3/Cell.hpp>

namespace match3 {

Cell::Cell(ConstBoardWkPtr board)
  : type(Type::None)
  , position()
  , board(std::move(board)) {}

std::ostream&
operator<<(std::ostream& os, const Cell& obj) {
	os << "{type: " << obj.type.get() << ", position: " << obj.position.get() << "}";
	return os;
}
} // namespace match3
