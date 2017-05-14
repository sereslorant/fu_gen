
#include "NodeEditorTest.h"

#include "ui_NodeEditorTest.h"

NodeEditorTest::NodeEditorTest()
	:ViewListener(*this)
{
	Ui::NodeEditorTest Ui;
	Ui.setupUi(this);
	//
	ComboBox = Ui.comboBox;
	ToolBox = Ui.toolBox;
	//
	EdgeVisualizer = Ui.widget;
	EdgeVisualizer->AddListener(&ViewListener);
}

NodeEditorTest::~NodeEditorTest()
{
	delete TurtleNode;
	delete HypergraphNode;
	delete MeshNode;
}

int main(int argc, char *argv[])
{
	QApplication Application(argc, argv);
	//
    NodeEditorTest Window;
    Window.show();
	//
    return Application.exec();
}
