//! @file

#include "StatWidget.hpp"

#include <QGroupBox>
#include <QHBoxLayout>

StatWidget::StatWidget(const QString& title, QWidget* parent)
  : QWidget(parent)
  , _textLabel() {
	_setupWidget(title);
}

StatWidget::~StatWidget() {}

QString
StatWidget::text() const {
	return _textLabel->text();
}

void
StatWidget::setText(const QString& text) {
	_textLabel->setText(text);
}

void
StatWidget::_setupWidget(const QString& title) {
	setObjectName("Stat");
	setStyleSheet(
	  "QWidget {"
	  "background-color: orange;"
	  "color: white;"
	  "font: bold;"
	  "}"

	  "QGroupBox {"
	  "border: 4px solid white;"
	  "border-radius: 12px;"
	  "margin-top: 2ex;"
	  "}"

	  "QGroupBox::title {"
	  "background-color: orange;"
	  "subcontrol-origin: margin;"
	  "subcontrol-position: top left;"
	  "border: 4px solid white;"
	  "border-radius: 6px;"
	  "padding: 0 2px;"
	  "}");

	setLayout(new QHBoxLayout());

	{
		QGroupBox* box = new QGroupBox(title);
		box->setObjectName("title");
		box->setMinimumWidth(QFontMetrics(box->font()).width(box->title()) * 2);
		QHBoxLayout* boxLayout = new QHBoxLayout;
		box->setLayout(boxLayout);

		_textLabel = new QLabel(QString::number(0));
		_textLabel->setObjectName("label");
		_textLabel->setAlignment(Qt::AlignRight);
		boxLayout->addWidget(_textLabel);

		layout()->addWidget(box);
	}
}
