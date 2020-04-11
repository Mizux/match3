//! @file

#include "GameWidget.hpp"

#include "StatWidget.hpp"
#include <QInputDialog>
#include <QVBoxLayout>

GameWidget::GameWidget(QWidget* parent)
  : QWidget(parent)
  , _game()
  , _resetButton()
  , _enemyWidget()
  , _boardView() {
	_game.setTypes({{"pkm_1"}});
	_game.resize({1, 1});
	_game.fillBoard();

	setStyleSheet(
	  "GameWidget {"
	  "background-color: "
	  "qlineargradient(x1:0,y1:1, x2:0,y2:0,"
	  "stop:0 #006000, stop:0.2 #008000, stop:0.25 #00AAFF, stop:1 #0080C0);"
	  "}"
	  "QPushButton {"
	  "background-color: "
	  "qlineargradient(x1:0,y1:0, x2:0,y2:1,"
	  "stop: 0 #FF80F0, stop: 1 #FF80A0);"
	  "color: white;"
	  "border-radius: 10px;"
	  "font: bold 16px;"
	  "padding: 6px;"
	  "}");
	_setupWidget();
}

#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>

void
GameWidget::slotResetBoard(void) {
	QDialog dialog(this);
	QMap<QString, QComboBox*> confs;
	{
		QFormLayout* form = new QFormLayout(&dialog);
		dialog.setLayout(form);
		form->addRow(new QLabel("Game configuration")); // title
		{
			QComboBox* comboBox = new QComboBox(&dialog);
			comboBox->addItem("6x6", QSize(6, 6));
			comboBox->addItem("8x6", QSize(8, 6));
			comboBox->addItem("6x8", QSize(6, 8));
			comboBox->addItem("8x8", QSize(8, 8));
			comboBox->setCurrentIndex(0);
			form->addRow("Board Size", comboBox);
			confs.insert("Size", comboBox);
		}
		{
			QComboBox* comboBox = new QComboBox(&dialog);
			comboBox->addItem("1", 1);
			comboBox->addItem("2", 2);
			comboBox->addItem("3", 3);
			comboBox->addItem("4", 4);
			comboBox->addItem("5", 5);
			comboBox->addItem("6", 6);
			comboBox->setCurrentIndex(0);
			form->addRow("Color Number", comboBox);
			confs.insert("Colors", comboBox);
		}
		QDialogButtonBox* buttonBox = new QDialogButtonBox(
		  QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
		form->addRow(buttonBox);
		QObject::connect(buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
		QObject::connect(buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
	}
	if (dialog.exec() == QDialog::Accepted) {
		// If the user didn't dismiss the dialog, do something with the fields
		match3::Size size;
		{
			QComboBox* combo = confs["Size"];
			QSize s          = combo->currentData().toSize();
			size[0]          = s.width();
			size[1]          = s.height();
		}
		match3::Types types;
		{
			QComboBox* combo = confs["Colors"];
			int number       = combo->currentData().toInt();
			for (int i = 1; i <= number; ++i) {
				types.addTypes({match3::Type("pkm_" + std::to_string(i))});
			}
		}

		_game.resize(size);
		_game.setTypes(types);
		_game.fillBoard();
		emit boardUpdated();
	}
}

void
GameWidget::_setupWidget() {
	setObjectName("Game");
	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);

	{ // Top Screen
		QHBoxLayout* topLayout = new QHBoxLayout();

		{ // Status Left
			QVBoxLayout* statusLayout = new QVBoxLayout();

			StatWidget* lvl = new StatWidget("Level", this);
			statusLayout->addWidget(lvl);
			StatWidget* score = new StatWidget("Score", this);
			statusLayout->addWidget(score);
			StatWidget* count = new StatWidget("Count", this);
			statusLayout->addWidget(count);
			QSpacerItem* spacer =
			  new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
			statusLayout->addItem(spacer);

			topLayout->addItem(statusLayout);
		}
		{ // Center
			_enemyWidget = new EnemyWidget(this);

			topLayout->addWidget(_enemyWidget);
		}
		{ // Status Right
			QVBoxLayout* statusLayout = new QVBoxLayout();

			QSpacerItem* spacer =
			  new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
			statusLayout->addItem(spacer);
			StatWidget* name = new StatWidget("Name", this);
			statusLayout->addWidget(name);

			topLayout->addItem(statusLayout);
		}
		layout()->addItem(topLayout);
	}

	{ // Bottom Screen
		_boardView = new BoardView(_game.board(), this);
		layout()->addWidget(_boardView);
	}

	{ // StatusBar
		QHBoxLayout* statusLayout = new QHBoxLayout();

		_resetButton = new QPushButton("Reset", this);
		_resetButton->setFixedSize(_resetButton->sizeHint());
		statusLayout->addWidget(_resetButton);
		QSpacerItem* spacer =
		  new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
		statusLayout->addItem(spacer);
		_returnButton = new QPushButton("Return", this);
		_returnButton->setFixedSize(_returnButton->sizeHint());
		statusLayout->addWidget(_returnButton);

		layout()->addItem(statusLayout);
	}

	QWidget::connect(
	  _resetButton, &QPushButton::clicked, this, &GameWidget::slotResetBoard);
	QWidget::connect(
	  this, &GameWidget::boardUpdated, _boardView, &BoardView::onBoardReset);
}
