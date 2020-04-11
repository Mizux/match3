//! @file
#pragma once

#include "Position.hpp"
#include "Type.hpp"
#include <Signal/Property.hpp>
#include <memory>
#include <ostream>
#include <string>

namespace match3 {
class Board;
using ConstBoardWkPtr = std::weak_ptr<const Board>;
using ConstBoardPtr   = std::shared_ptr<const Board>;

//! @brief Entity use to store an item on the board.
class Item {
	public:
	//! @brief Default constructor.
	//! @param[in] board Board which Item belongs to.
	//! @param[in] type Type of the item.
	//! @param[in] pos Position of the item in the board.
	Item(Type type, Position pos, ConstBoardWkPtr board = ConstBoardWkPtr());
	//! @brief Destructs the object.
	~Item() = default;

	//! @brief Constructs an object with the copy of the content of other.
	Item(const Item&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Item& operator=(const Item&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Item(Item&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Item& operator=(Item&&) = default;

	//! @brief Gets Type of this Item.
	Signal::Property<Type> type;

	//! @brief Position of the Item.
	Signal::Property<Position> position;

	//! @brief Signal emited when an item is destroyed.
	Signal::Property<bool> alive;

	//! @brief Stores Board Parent.
	Signal::Property<ConstBoardWkPtr> board;

	//! @brief Finds match with this item.
	//! @note return false, if item is not attached to a board.
	//! @return true if there is at least one match in the board.
	bool hasMatch() const noexcept;

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Item instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Item& obj);

	protected:
	//! @brief Checks if item can form a match along X axis.
	//! @param[in] board The board to use.
	//! @return true if item could perform match(s), false otherwise.
	bool _hasMatchX(ConstBoardPtr board) const noexcept;
	//! @brief Checks if item can form a match along Y axis.
	//! @param[in] board The board to use.
	//! @return true if item could perform match(s), false otherwise.
	bool _hasMatchY(ConstBoardPtr board) const noexcept;
};

//! @brief Shared pointer of Item.
using ItemPtr = std::shared_ptr<Item>;
//! @brief Shared pointer of const Item.
using ConstItemPtr = std::shared_ptr<const Item>;
} // namespace match3
