
#include "PipelineVisualizationTest.h"

#include "ui_PipelineVisualizationTest.h"

PipelineVisualizationTest::PipelineVisualizationTest()
    :ViewListener(*this)
{
    Ui::PipelineVisualizationTest Ui;
	Ui.setupUi(this);
    //
    PipelineEditor = Ui.PipelineEditor;
    EdgeVisualizer = Ui.EdgeVisualizer;
    //
    EdgeVisualizer->AddListener(&ViewListener);
}

PipelineVisualizationTest::~PipelineVisualizationTest()
{
    delete TestNodePresenter1;
    delete TestNodePresenter2;
    delete TestNodePresenter3;
    /*delete TestEdgePresenter1;
    delete TestEdgePresenter2;
    delete TestEdgePresenter3;*/
    delete TestPipelinePresenter;
}

#include "PipelineVisualizationTest.moc"

/*
 * Main test
 */

#include <QtWidgets/QApplication>

int main(int argc,char *argv[])
{
	QApplication Application(argc, argv);
	//
    PipelineVisualizationTest Window;
    Window.show();
	//
    return Application.exec();
}
