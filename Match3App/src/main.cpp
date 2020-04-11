#include <QApplication>

#include "GameWidget.hpp"

int
main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	app.setOrganizationName("Mizux");
	app.setApplicationName("Match3");

	// MainWindow main;
	GameWidget main;
	main.show();
	return app.exec();
}
