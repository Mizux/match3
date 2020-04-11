//! @file
#pragma once

#include <QGraphicsPixmapItem>
#include <QGraphicsView>

class EnemyWidget : public QGraphicsView {
	Q_OBJECT

	public:
	EnemyWidget(QWidget* parent = 0);
	virtual ~EnemyWidget();
	EnemyWidget(const EnemyWidget&) = delete;
	EnemyWidget& operator=(const EnemyWidget&) = delete;

	QSize sizeHint() const;
	public slots:
	void setEnemy(QPixmap sprite);

	protected:
	virtual void resizeEvent(QResizeEvent* event);

	private:
	QGraphicsPixmapItem* _sprite;

	void _setupWidget();
};
