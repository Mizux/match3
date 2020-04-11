//! @file
#include <Match3/Item.hpp>

#include <Match3/Board.hpp>

namespace match3 {

Item::Item(Type type, Position pos, ConstBoardWkPtr board)
  : type(std::move(type))
  , position(std::move(pos))
  , alive(true)
  , board(std::move(board)) {}

bool
Item::hasMatch() const noexcept {
	ConstBoardPtr boardSP = board.get().lock();
	if (!boardSP) return false;
	return _hasMatchX(boardSP) || _hasMatchY(boardSP);
}

std::ostream&
operator<<(std::ostream& os, const Item& obj) {
	os << "{type: " << obj.type.get() << ", position: " << obj.position.get()
	   << ", status: " << obj.alive.get() << "}";
	return os;
}

bool
Item::_hasMatchX(ConstBoardPtr board) const noexcept {
	std::size_t length = 1;
	// search on the left side
	for (Position p = position.get() - Position(1, 0); p.x() >= 0; --p.x()) {
		ConstItemPtr it = board->item(p);
		if (!it || it->type.get() != type.get()) break;
		length++;
	}
	// search on the right side
	for (Position p = position.get() + Position(1, 0); p.x() < int(board->size().x());
	     ++p.x()) {
		ConstItemPtr it = board->item(p);
		if (!it || it->type.get() != type.get()) break;
		length++;
	}
	return length >= 3;
}

bool
Item::_hasMatchY(ConstBoardPtr board) const noexcept {
	std::size_t length = 1;
	// search below the item
	for (Position p = position.get() - Position(0, 1); p.y() >= 0; --p.y()) {
		ConstItemPtr it = board->item(p);
		if (!it || it->type.get() != type.get()) break;
		length++;
	}
	// search above the item
	for (Position p = position.get() + Position(0, 1); p.y() < int(board->size().y());
	     ++p.y()) {
		ConstItemPtr it = board->item(p);
		if (!it || it->type.get() != type.get()) break;
		length++;
	}
	return length >= 3;
}
} // namespace match3
