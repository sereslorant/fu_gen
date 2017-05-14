
#include "NodeEditorAndPipelineTest.h"

#include "ui_NodeEditorAndPipelineTest.h"

NodeEditorAndPipelineTest::NodeEditorAndPipelineTest()
{
	Ui::NodeEditorAndPipelineTest Ui;
	Ui.setupUi(this);
	//
	TestNodeEditor = Ui.NodeEditor;
	PipelineEditor = Ui.PipelineEditor;
	//
	Test();
}

NodeEditorAndPipelineTest::~NodeEditorAndPipelineTest()
{
	delete TestPresenter;
	delete TestEditorListener;
}

#include "NodeEditorAndPipelineTest.moc"

/*
 * Main test
 */

#include <QtWidgets/QApplication>

int main(int argc,char *argv[])
{
	QApplication Application(argc, argv);
	//
    NodeEditorAndPipelineTest Window;
    Window.show();
	//
    return Application.exec();
}
