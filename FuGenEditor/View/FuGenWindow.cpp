
#include "FuGenWindow.h"
#include "ui_FuGenWindow.h"

#include "PipelineEditor/FuGenPipelineNode.h"

FuGenWindow::FuGenWindow()
	:ViewListener(this)
{
	Ui::FuGenWindow Ui;
	Ui.setupUi(this);
	//
	PipelineEditor		= Ui.PipelineEditor;
	NodeEditor			= Ui.NodeEditor;
	EdgeVisualizer		= Ui.EdgeVisualizer;
	//PipelineElementList	= Ui.PipelineElementList;
	//
	EdgeVisualizer->AddListener(&ViewListener);
}

FuGenWindow::~FuGenWindow()
{
	delete PipelineEditor;
	//delete EditorListener;
}

#include "FuGenWindow.moc"
