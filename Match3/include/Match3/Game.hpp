//! @file
#pragma once

#include "Board.hpp"
#include "Types.hpp"
#include <memory>
#include <unordered_set>

namespace match3 {

//! @brief Stores a Match3 game instance.
class Game {
	public:
	//! @brief Builds a match3 game of specified size.
	//! @param[in] size Size of the board.
	explicit Game(Size size = {0, 0});

	//! @brief Gets current score.
	//! @return Current score.
	std::size_t score() const noexcept;

	//! @brief Gets the underlying Board object.
	//! @return The @ref Board instance.
	ConstBoardPtr board() const noexcept;

	//! @brief Gets the list of Type currently in use.
	//! @return The @ref Type list without special Type.
	ConstTypesPtr types() const noexcept;

	//! @brief Gets the current size of the Board.
	//! @return The Board size.
	const Size& size() const noexcept;
	//! @brief Resizes the Board to the specified dimension.
	//! @param[in] size THe new size requested.
	//! @note The score is reset to zero.
	//! @note This method clear the Board from previous items.
	//! @note This method clear the Board from previous cells.
	void resize(const Size& size);

	//! @brief Clears the board.
	//! @post The score is set to zero.
	//! @post All items are removed.
	void clear() noexcept;
	//! @brief Resets the board.
	//! @post The score is set to zero.
	//! @post All items are removed.
	//! @post All previous Types are removed.
	void reset() noexcept;

	//! @brief Sets the list of allowed Types.
	//! @post The score is set to zero.
	//! @post All items are removed.
	//! @post All previous Types are removed.
	//! @param[in] types The new Types requested.
	void setTypes(const Types& types);
	//! @brief Fills the board with new items.
	//! @note First Game is cleared.
	void fillBoard();

	protected:
	//! @brief Stores score.
	std::size_t _score;
	//! @brief Stores list of Types currently in use.
	std::shared_ptr<Types> _types;
	//! @brief Stores Board instance.
	std::shared_ptr<Board> _board;
};
} // namespace match3
