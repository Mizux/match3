//! @file

#include "Entity.hpp"
#include <QCursor>
#include <QPainter>
#include <QPixmapCache>

Entity::Entity(const match3::ConstItemPtr& entity, QGraphicsItem* parent)
  : QGraphicsObject(parent)
  , _entity(entity)
  , _dragStart(false) {
	setPos(_entity->position.get().x(), _entity->position.get().y());
	setTransformOriginPoint(0.5, 0.5);
	setZValue(1);

	setCursor(Qt::OpenHandCursor);
}

QRectF
Entity::boundingRect() const {
	return QRectF(QPointF(0, 0), QPointF(1, 1));
}

void
Entity::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
	painter->setRenderHint(QPainter::Antialiasing);
	painter->setRenderHint(QPainter::SmoothPixmapTransform);

	if (_dragStart) painter->setOpacity(0.5);

	painter->drawPixmap(QRect(0, 0, 1, 1), pixmap());
}

QPixmap
Entity::pixmap() {
	std::string name = _entity->type.get().name();

	QPixmap pm;
	if (!QPixmapCache::find(QString::fromStdString(name), &pm)) {
		pm.load(":/img/" + QString::fromStdString(name) + ".png");
		QPixmapCache::insert(QString::fromStdString(name), pm);
	}
	return pm;
}

void
Entity::dragStart() {
	_dragStart = true;
	update();
}

void
Entity::dragStop() {
	_dragStart = false;
	update();
}
