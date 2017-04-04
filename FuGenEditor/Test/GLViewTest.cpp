
#include "GLViewTest.h"

#include "ui_GLViewTest.h"

GLViewTest::GLViewTest()
{
	Ui::GLViewTest Ui;
	Ui.setupUi(this);
}

GLViewTest::~GLViewTest()
{
}

#include "GLViewTest.moc"

/*
 * Main test
 */

#include <QtWidgets/QApplication>

int main(int argc,char *argv[])
{
	QApplication Application(argc, argv);
	//
    GLViewTest Window;
    Window.show();
	//
    return Application.exec();
}
