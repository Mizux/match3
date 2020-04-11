//! @file
#pragma once

#include <Match3/Item.hpp>
#include <QGraphicsObject>

class Entity : public QGraphicsObject {
	public:
	Entity(const match3::ConstItemPtr& entity, QGraphicsItem* parent = 0);
	virtual ~Entity() = default;

	QRectF boundingRect() const override;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

	QPixmap pixmap();

	void dragStart();
	void dragStop();

	protected:
	const match3::ConstItemPtr _entity;
	bool _dragStart;
};
