//! @file
#pragma once

#include "Cell.hpp"
#include "Item.hpp"
#include "Size.hpp"
#include "Types.hpp"
#include <memory>
#include <ostream>
#include <unordered_set>

namespace match3 {
class Cell;
using CellPtr      = std::shared_ptr<match3::Cell>;
using ConstCellPtr = std::shared_ptr<const match3::Cell>;
class Item;
using ItemPtr      = std::shared_ptr<Item>;
using ConstItemPtr = std::shared_ptr<const Item>;

/*! @brief Store a match3 board
 * @details
 * - by default item fall from up to bottom
 * - by default swap is possible only if this move generates match.
 * - Position {0, 0} (i.e. origin) is at the @b bottom left @b of the Grid.*/
class Board : public std::enable_shared_from_this<Board> {
	public:
	//! @brief Build an empty Board.
	//! @warning Can't set a size in ctor since Cells will need board weak pointer
	//! which will be valide on ctor return...
	//! @param[in] types Types to use to fill the board.
	explicit Board(ConstTypesWkPtr types);
	//! @brief Destructs the object.
	~Board() = default;

	//! @brief Constructs an object with the copy of the content of other.
	Board(const Board&) = default;
	//! @brief Replaces the contents with a copy of the contents of other.
	//! @return *this.
	Board& operator=(const Board&) = default;
	//! @brief Constructs an object with the contents of other using move semantics.
	Board(Board&&) = default;
	//! @brief Replaces the contents with those of other using move semantics.
	//! @return *this.
	Board& operator=(Board&&) = default;

	//! @brief Clear the board by removing all items.
	void clear();

	//! @brief Retrieve the size of the board.
	//! @return The current size of the board.
	const Size& size() const noexcept;
	/*! @brief Resize the board to the specified size.
	 * @details All @ref Cell and @ref Item will be remove.
	 * then new cells will be created to fill the new dimension.
	 * @param[in] size The new size requested.*/
	void resize(Size size);

	/*! @brief Return all @ref Cell "Cells" in the board.
	 * @return List of @ref Cell "Cell(s)" pointer.*/
	std::vector<ConstCellPtr> cells() const;
	//! @copydoc cells() const.
	std::vector<CellPtr> cells();
	/*! @brief Return @ref Cell that is at the specified Position.
	 * @param[in] pos Position of the element requested.
	 * @return Pointer on the requested @ref Cell if success, empty pointer
	 * otherwise.*/
	ConstCellPtr cell(const Position& pos) const;
	//! @copydoc cell(const Position&) const.
	CellPtr cell(const Position& pos);

	/*! @brief Returns all @ref Item "Items" in the board.
	 * @return List of @ref Item "item(s)" pointer.*/
	std::vector<ConstItemPtr> items() const;
	//! @copydoc items() const.
	std::vector<ItemPtr> items();
	/*! @brief Return @ref Item that is at the specified Position.
	 * @param[in] pos Position of the element requested.
	 * @return @ref Item if present.*/
	ConstItemPtr item(const Position& pos) const;
	//! @copydoc item(const Position&) const.
	ItemPtr item(const Position& pos);

	//! @brief Adds a new item to the board.
	//! @param[in] item The new item to add.
	//! @throw std::runtime_error if there is already an Item at the position
	//! specified by the Item.
	void addItem(ItemPtr item);
	//! @brief Adds several @ref Item "items" to the board.
	//! @param[in] items The new items to add.
	//! @throw std::runtime_error if there is already an Item at the position
	//! specified by the Item.
	void addItems(const std::vector<ItemPtr>& items);

	//! @brief Removes @ref Item at position specified from board.
	//! @param[in] pos Position of the item to remove.
	//! @return The Item removed if any.
	ItemPtr removeItem(const Position& pos);
	//! @brief Removes @ref Item specified from the board.
	//! @param[in] item Item of the board to remove.
	//! @return The Item removed if any.
	ItemPtr removeItem(const ConstItemPtr& item);
	//! @brief Removes several @ref Item "items" from the board.
	//! @param[in] positions Positions of the items to remove.
	//! @return The list of removed items.
	std::vector<ItemPtr> removeItems(const std::vector<Position>& positions);
	//! @brief Removes several @ref Item "Items".
	//! @param[in] items List of items to remove.
	//! @return The list of removed items.
	std::vector<ItemPtr> removeItems(const std::vector<ConstItemPtr>& items);

	//! @brief Lists of available gravity direction.
	enum class Gravity { Up, Down, Left, Right, None };
	//! @brief Get current gravity direction use to move Item.
	//! @return the Gravity direction.
	Gravity gravity() const noexcept;
	//! @brief Updates the Gravity direction use to move Item.
	//! @param[in] gravity The Gravity direction requested.
	void setGravity(const Gravity& gravity) noexcept;

	//! @brief Fills board with items
	//! @note @ref Type::Any and @ref Type::None are not use for filling board.
	//! @note all previous items will be removed.
	void fill();

	//! @brief Checks if item at position specified can form a match.
	//! @param[in] pos The Position requested.
	//! @return true if item could perform match(s), false otherwise.
	bool hasMatch(const Position& pos) const noexcept;
	//! @brief Checks if item specified can form a match.
	//! @param[in] item The item to check.
	//! @return true if item could perform match(s), false otherwise.
	bool hasMatch(const ConstItemPtr& item) const noexcept;
	//! @brief Checks if there is at least one match available.
	//! @return true if there is at least one match in the board.
	bool hasMatch() const noexcept;

	//! @brief Gets list of item which form a match.
	//! @return List of items doing a match.
	std::vector<ConstItemPtr> getMatches() const;

	//! @brief Finds matches in the board and return list of Item removed.
	//! @return List of items removed from the board.
	std::vector<ItemPtr> findandRemoveMatches();
	//! @brief Find and move items which can fall.
	//! @return List of items whose position has changed.
	std::vector<ItemPtr> iterate();

	//! @brief Stream operator for debug purpose.
	//! @param[in,out] os Stream to write.
	//! @param[in] obj Board instance to log.
	//! @return the output stream.
	friend std::ostream& operator<<(std::ostream& os, const Board& obj);

	protected:
	//! @brief Stores reference to game (e.g. to get type list).
	ConstTypesWkPtr _types;
	//! @brief Stores the current size of the board.
	Size _size;
	//! @brief Stores each tile in the board.
	std::unordered_set<CellPtr> _cells;
	//! @brief Stores each item in the board.
	std::unordered_set<ItemPtr> _items;

	//! @brief Stores gravity direction, by default item fall down.
	enum Gravity _gravity;

	//! @brief Checks if item at position specified can form a match along X axis.
	//! @param[in] pos The Position to check.
	//! @return true if item could perform match(s), false otherwise.
	bool _hasMatchX(const Position& pos) const noexcept;
	//! @brief Checks if item at position specified can form a match along Y axis.
	//! @param[in] pos The Position to check.
	//! @return true if item could perform match(s), false otherwise.
	bool _hasMatchY(const Position& pos) const noexcept;
};

//! @brief Shared pointer of Board.
using BoardPtr = std::shared_ptr<Board>;
//! @brief Shared pointer of const Board.
using ConstBoardPtr = std::shared_ptr<const Board>;
//! @brief Weak pointer of Board.
using BoardWkPtr = std::weak_ptr<Board>;
//! @brief Weak pointer of const Board.
using ConstBoardWkPtr = std::weak_ptr<const Board>;
} // namespace match3
