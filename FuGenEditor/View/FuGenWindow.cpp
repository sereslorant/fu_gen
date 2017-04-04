
#include "FuGenWindow.h"
#include "ui_FuGenWindow.h"

#include "PipelineEditor/FuGenPipelineNode.h"

void SetupDemoPipelineEditor(FuGenPipelineEditor *PipelineEditor)
{
	PipelineEditor->setMinimumSize(QSize(350,350));
	//PipelineEditor->setAcceptDrops(true);
	//
	PipelineEditor->AddNode(160,150);
	PipelineEditor->AddNode(20,20);
	PipelineEditor->AddNode(60,100);
	PipelineEditor->AddNode(100,130);
	PipelineEditor->AddNode(60,140);
	PipelineEditor->AddNode(60,150);
};

FuGenWindow::FuGenWindow()
{
	Ui::FuGenWindow Ui;
	Ui.setupUi(this);
	//
	EdgeVisualizer		= Ui.EdgeVisualizer;
	PipelineElementList	= Ui.PipelineElementList;
	//
	SetupDemoPipelineEditor(Ui.PipelineEditor);
}

FuGenWindow::~FuGenWindow()
{}

#include "FuGenWindow.moc"
