//! @file
#pragma once

#include <Match3/Cell.hpp>
#include <QGraphicsObject>

class Tile : public QGraphicsObject {
	public:
	Tile(const match3::ConstCellPtr& cell, QGraphicsItem* parent = 0);
	virtual ~Tile() = default;

	QRectF boundingRect() const override;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

	QPixmap pixmap();

	protected:
	const match3::ConstCellPtr _cell;

	//! @brief Call when DragDrop item enter in the bounding rect of this object.
	void dragEnterEvent(QGraphicsSceneDragDropEvent* event) override;
	//! @brief Call when DragDrop item leave the bounding rect of this object.
	void dragLeaveEvent(QGraphicsSceneDragDropEvent* event) override;
	//! @brief Call when DragDrop item is drop on this object. (i.e. release mouse
	//! button).
	void dropEvent(QGraphicsSceneDragDropEvent* event) override;

	bool _dragOver;
};
