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

//! @brief Entity use to store status of a tile board.
class Cell {
	public:
	//! @brief Constructs an empty object.
	//! @param[in] board Board which Cell belongs to.
	explicit Cell(ConstBoardWkPtr board = ConstBoardWkPtr());
	//! @brief Destructs the object.
	~Cell() = default;

	//! @brief Constructs an object with the copy of the content of other.
	Cell(const Cell&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Cell& operator=(const Cell&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Cell(Cell&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Cell& operator=(Cell&&) = default;

	//! @brief Get type of this item.
	Signal::Property<Type> type;

	//! @brief Position of the Cell.
	Signal::Property<Position> position;

	//! @brief Store Board Parent.
	Signal::Property<ConstBoardWkPtr> board;

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Cell instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Cell& obj);
};

//! @brief Shared pointer of Cell.
using CellPtr = std::shared_ptr<match3::Cell>;
//! @brief Shared pointer of const Cell.
using ConstCellPtr = std::shared_ptr<const match3::Cell>;
} // namespace match3
