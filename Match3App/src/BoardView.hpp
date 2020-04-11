//! @file
#pragma once

#include "Entity.hpp"
#include "Tile.hpp"
#include <Match3/Board.hpp>
#include <QGraphicsView>
#include <QSet>

class BoardView : public QGraphicsView {
	Q_OBJECT

	public:
	BoardView(const match3::ConstBoardPtr& board, QWidget* parent = 0);
	virtual ~BoardView() = default;

	QSize sizeHint() const override;
	int heightForWidth(int w) const override;

	void setDropPos(const QPointF& pos);

	QSize boardSize() const;
	void setBoardSize(QSize size);

	QSize tileSize() const;
	void setTileSize(QSize tile);

	public slots:
	//! @brief Clear all, and recreate them if any.
	void onBoardReset();

	protected:
	virtual void resizeEvent(QResizeEvent* event) override;
	//! @brief When clic on item, perform Drag&Drop.
	virtual void mousePressEvent(QMouseEvent* event) override;

	void _setupWidget();

	match3::ConstBoardPtr _board;
	QSize _minTileSize;
	QSet<Tile*> _tiles;
	QSet<Entity*> _entities;

	QPointF _dropPos;
};
