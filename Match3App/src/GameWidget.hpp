//! @file
#pragma once

#include <QWidget>

#include "BoardView.hpp"
#include "EnemyWidget.hpp"
#include <Match3/Game.hpp>
#include <QPushButton>

class GameWidget : public QWidget {
	Q_OBJECT

	public:
	GameWidget(QWidget* parent = 0);
	virtual ~GameWidget() = default;

	signals:
	void boardUpdated();

	public slots:
	void slotResetBoard(void);

	private:
	match3::Game _game;

	QPushButton* _resetButton;
	QPushButton* _returnButton;

	EnemyWidget* _enemyWidget;
	BoardView* _boardView;

	void _setupWidget();
};
