#include <QtWidgets/QApplication>

#include "FuGenWindow.h"

int main(int argc, char** argv)
{
    QApplication Application(argc, argv);
	QApplication::setStartDragDistance(5);
	//
    FuGenWindow Window;
    Window.show();
	//
    return Application.exec();
}
