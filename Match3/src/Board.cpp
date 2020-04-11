//! @file
#include <Match3/Board.hpp>

#include <Match3/Types.hpp>
#include <algorithm>
#include <random>

namespace match3 {
Board::Board(ConstTypesWkPtr types)
  : _types(std::move(types))
  , _size({0, 0})
  , _gravity(Gravity::Down) {}

void
Board::clear() {
	_items.clear();
	for (const CellPtr& cell : _cells) {
		cell->type.set(Type::None);
	}
}

const Size&
Board::size() const noexcept {
	return _size;
}

void
Board::resize(Size size) {
	_items.clear();
	_cells.clear();

	_size = std::move(size);
	for (Size::value_type i = 0; i < _size.x(); ++i) {
		for (Size::value_type j = 0; j < _size.y(); ++j) {
			CellPtr cell = std::make_shared<Cell>(shared_from_this());
			cell->position.set(Position(i, j));
			_cells.insert(cell);
		}
	}
}

std::vector<ConstCellPtr>
Board::cells() const {
	std::vector<ConstCellPtr> res;
	res.reserve(_cells.size());
	for (const auto& it : _cells)
		res.push_back(it);
	return res;
}

std::vector<CellPtr>
Board::cells() {
	std::vector<CellPtr> res;
	res.reserve(_cells.size());
	for (const auto& it : _cells)
		res.push_back(it);
	return res;
}

ConstCellPtr
Board::cell(const Position& pos) const {
	std::unordered_set<CellPtr>::const_iterator res =
	  std::find_if(_cells.begin(), _cells.end(), [&pos](const CellPtr& it) {
		  return it->position.get() == pos;
	  });
	if (res != _cells.end())
		return *res;
	else
		return ConstCellPtr();
}

CellPtr
Board::cell(const Position& pos) {
	std::unordered_set<CellPtr>::iterator res =
	  std::find_if(_cells.begin(), _cells.end(), [&pos](const CellPtr& it) {
		  return it->position.get() == pos;
	  });
	if (res != _cells.end())
		return *res;
	else
		return CellPtr();
}

std::vector<ConstItemPtr>
Board::items() const {
	std::vector<ConstItemPtr> res;
	res.reserve(_items.size());
	for (const auto& it : _items)
		res.push_back(it);
	return res;
}

std::vector<ItemPtr>
Board::items() {
	std::vector<ItemPtr> res;
	res.reserve(_items.size());
	for (const auto& it : _items)
		res.push_back(it);
	return res;
}

ConstItemPtr
Board::item(const Position& pos) const {
	std::unordered_set<ItemPtr>::const_iterator res =
	  std::find_if(_items.begin(), _items.end(), [&pos](const ItemPtr& it) {
		  return it->position.get() == pos;
	  });
	if (res != _items.end())
		return *res;
	else
		return ConstItemPtr();
}

ItemPtr
Board::item(const Position& pos) {
	std::unordered_set<ItemPtr>::iterator res =
	  std::find_if(_items.begin(), _items.end(), [&pos](const ItemPtr& it) {
		  return it->position.get() == pos;
	  });
	if (res != _items.end())
		return *res;
	else
		return ItemPtr();
}

void
Board::addItem(ItemPtr it) {
	if (item(it->position.get())) {
		throw std::runtime_error("Item already at this position.");
	}
	it->board.set(shared_from_this());
	_items.insert(it);
}

ItemPtr
Board::removeItem(const Position& pos) {
	std::unordered_set<ItemPtr>::iterator it =
	  std::find_if(_items.begin(), _items.end(), [&pos](const ItemPtr& item) {
		  return item->position.get() == pos;
	  });
	if (it != _items.end()) {
		ItemPtr res = *it;
		res->alive.set(false);
		_items.erase(it);
		return res;
	} else
		return ItemPtr();
}

ItemPtr
Board::removeItem(const ConstItemPtr& item) {
	if (item) return removeItem(item->position.get());
	return ItemPtr();
}

std::vector<ItemPtr>
Board::removeItems(const std::vector<Position>& positions) {
	std::vector<ItemPtr> res;
	res.reserve(positions.size());
	for (const auto& pos : positions) {
		ItemPtr it = removeItem(pos);
		if (it) res.push_back(it);
	}
	return res;
}

std::vector<ItemPtr>
Board::removeItems(const std::vector<ConstItemPtr>& items) {
	std::vector<ItemPtr> res;
	res.reserve(items.size());
	for (const ConstItemPtr& it : items) {
		ItemPtr tmp = removeItem(it);
		if (tmp) res.push_back(tmp);
	}
	return res;
}

Board::Gravity
Board::gravity() const noexcept {
	return _gravity;
}

void
Board::setGravity(const Gravity& gravity) noexcept {
	_gravity = gravity;
}

void
Board::fill() {
	//! <OL>
	clear();

	//! <LI> Create all items
	{
		// Get Types
		ConstTypesPtr types = _types.lock();
		if (!types || types->size() == 0) {
			throw std::runtime_error("Types empty.");
		}
		// Create uniform random generator for item's type
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, types->size() - 1);

		std::vector<Type> typeNames;
		typeNames.reserve(types->size());
		for (auto const& it : *types) {
			typeNames.push_back(it.name());
		}
		// Create item using the generator.
		for (const CellPtr& cPtr : _cells) {
			_items.insert(std::make_shared<Item>(
			  typeNames[dis(gen)], cPtr->position.get(), shared_from_this()));
		}
	}
	//! </OL>
}

bool
Board::hasMatch(const Position& pos) const noexcept {
	ConstItemPtr it = item(pos);
	if (it)
		return it->hasMatch();
	else
		return false;
}

bool
Board::hasMatch(const ConstItemPtr& item) const noexcept {
	return item->hasMatch();
}

bool
Board::hasMatch() const noexcept {
	for (const ItemPtr& item : _items) {
		if (item->hasMatch()) return true;
	}
	return false;
}

std::vector<ConstItemPtr>
Board::getMatches() const {
	std::vector<ConstItemPtr> res;
	for (const ItemPtr& item : _items) {
		if (item->hasMatch()) res.push_back(item);
	}
	return res;
}

std::vector<ItemPtr>
Board::findandRemoveMatches() {
	return removeItems(getMatches());
}

std::vector<ItemPtr>
Board::iterate() {
	std::vector<ItemPtr> res;

	if (_gravity == Gravity::Down) {
		for (int j = 0; j < int(_size.y() - 1); ++j) {
			for (int i = 0; i < int(_size.x()); ++i) {
				ItemPtr upperItem   = item({i, j + 1});
				ItemPtr currentItem = item({i, j});
				if ((!currentItem) && upperItem) {
					upperItem->position.set({i, j});
					res.push_back(upperItem);
				}
			}
		}
	} else
		throw std::runtime_error("Gravity direction not supported yet.");
	return res;
}

std::ostream&
operator<<(std::ostream& os, const Board& obj) {
	os << "Size: " << obj._size << std::endl;
	os << "Items: ";
	for (const auto& it : obj._items)
		os << "{" << *it << "}, ";
	os << "Cells: ";
	for (const auto& it : obj._cells)
		os << "{" << *it << "}, ";
	return os;
}
} // namespace match3
