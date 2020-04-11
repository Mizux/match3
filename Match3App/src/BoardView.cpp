//! @file

#include "BoardView.hpp"

#include "Entity.hpp"
#include "Tile.hpp"
#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>

BoardView::BoardView(const match3::ConstBoardPtr& board, QWidget* parent)
  : QGraphicsView(parent)
  , _board(board)
  , _minTileSize(48, 48)
  , _tiles()
  , _entities() {
	_setupWidget();
}

QSize
BoardView::sizeHint() const {
	return QSize(_board->size().x() * _minTileSize.width(),
	             _board->size().y() * _minTileSize.height());
}

int
BoardView::heightForWidth(int w) const {
	return w * _board->size().y() / _board->size().x();
}

void
BoardView::setDropPos(const QPointF& pos) {
	_dropPos = pos;
}

void
BoardView::onBoardReset() {
	scene()->clear();

	// Create Cell
	for (int j = 0; j < int(_board->size().y()); ++j) {
		for (int i = 0; i < int(_board->size().x()); ++i) {
			match3::ConstCellPtr cell = _board->cell({i, j});
			if (cell) {
				Tile* tile = new Tile(cell);
				scene()->addItem(tile);
				_tiles.insert(tile);
			}
		}
	}

	// Create Item
	for (int j = 0; j < int(_board->size().y()); ++j) {
		for (int i = 0; i < int(_board->size().x()); ++i) {
			match3::ConstItemPtr item = _board->item({i, j});
			if (item) {
				Entity* entity = new Entity(item);
				scene()->addItem(entity);
				_entities.insert(entity);
			}
		}
	}

	scene()->setSceneRect(0, 0, _board->size().x(), _board->size().y());
	fitInView(sceneRect(), Qt::KeepAspectRatio);
}

void
BoardView::resizeEvent(QResizeEvent* event) {
	fitInView(sceneRect(), Qt::KeepAspectRatio);
	QGraphicsView::resizeEvent(event);
}

void
BoardView::mousePressEvent(QMouseEvent* event) {
	// Find Entity at mouse position
	if (Entity* dragEntity = dynamic_cast<Entity*>(itemAt(event->pos()))) {
		dragEntity->dragStart();

		// Then create DragDrop event
		{
			QDrag* drag     = new QDrag(this);
			QMimeData* data = new QMimeData;
			data->setData("application/x-items", QByteArray());
			drag->setMimeData(data);

			// A tile size = 1x1 * fitInView Factor
			// HotSpot = middle of the tile
			QTransform tf = transform();
			drag->setHotSpot(QPoint((tf.m11() + 0.5) / 2, (tf.m22() + 0.5) / 2));
			drag->setPixmap(dragEntity->pixmap().scaledToWidth(tf.m11()));
			_dropPos = QPointF(-1.0, -1.0);
			if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
				// Verify if item is also present on drop site
				if (Entity* dropEntity =
				      dynamic_cast<Entity*>(itemAt(mapFromScene(_dropPos)))) {
					dropEntity->setPos(dragEntity->pos());
				}
				dragEntity->setPos(_dropPos);
			}
		}
		dragEntity->dragStop();
	}
}

void
BoardView::_setupWidget() {
	setObjectName("Board");
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	QSizePolicy policy;
	policy.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
	policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
	policy.setHeightForWidth(true);
	setSizePolicy(policy);

	setScene(new QGraphicsScene(this));

	setStyleSheet("background: transparent");
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

	onBoardReset();
}
