//! @file

#include "EnemyWidget.hpp"

#include <QGraphicsPixmapItem>

EnemyWidget::EnemyWidget(QWidget* parent)
  : QGraphicsView(parent)
  , _sprite() {
	_setupWidget();
}

EnemyWidget::~EnemyWidget() {}

void
EnemyWidget::setEnemy(QPixmap sprite) {
	_sprite->setPixmap(sprite);
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

QSize
EnemyWidget::sizeHint() const {
	return QSize(width(),
	             width() * _sprite->pixmap().height() / _sprite->pixmap().width());
}

void
EnemyWidget::resizeEvent(QResizeEvent* event) {
	fitInView(sceneRect(), Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(event);
}

void
EnemyWidget::_setupWidget() {
	setObjectName("Enemy");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QSizePolicy policy;
	policy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);

	setScene(new QGraphicsScene());

	setStyleSheet("background: transparent");
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	_sprite = new QGraphicsPixmapItem(QPixmap(":/img/pkm_1.png"));
	_sprite->setTransformationMode(Qt::SmoothTransformation);
	scene()->addItem(_sprite);
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}
