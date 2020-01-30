#include "gui/MainWindow.h"
#include <QApplication>
#include <QVector>

Q_DECLARE_METATYPE(std::vector<double>)
Q_DECLARE_METATYPE(size_t);
using namespace std;


int main(int argc, char* argv[])
{
	QApplication app(argc,argv);
	qRegisterMetaType<std::vector<double>>("std::vector<double>");
	qRegisterMetaType<size_t>("size_t");
	MainWindow mainWindow;
	mainWindow.show();
	return app.exec();

}
