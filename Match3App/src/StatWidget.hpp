//! @file
#pragma once

#include <QLabel>
#include <QWidget>

class StatWidget : public QWidget {
	Q_OBJECT

	public:
	StatWidget(const QString& title, QWidget* parent = 0);
	virtual ~StatWidget();
	StatWidget(const StatWidget&) = delete;
	StatWidget& operator=(const StatWidget&) = delete;

	QString text() const;
	void setText(const QString& text);

	private:
	QLabel* _textLabel;

	void _setupWidget(const QString& title);
};
