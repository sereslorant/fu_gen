#ifndef NODE_EDITOR_AND_PIPELINE_TEST_H
#define NODE_EDITOR_AND_PIPELINE_TEST_H

#include <Presenter/Data/TreeSkeletonPresenter.h>
#include <Presenter/Data/TreeHypergraphPresenter.h>
#include <Presenter/Data/TreeMeshPresenter.h>

#include <Presenter/PipelinePresenter.h>

#include <View/EdgeVisualizer/FuGenGLView.h>

#include <View/PipelineEditor/FuGenPipelineEditor.h>

#include <QStackedWidget>

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>

#include <View/NodeEditor/FuGenNodeEditor.h>


class PipelineEditorListener : public IPipelineListener
{
private:
	FuGenPipelineEditor *PipelineEditor;
	//
public:
	//
	virtual void TurtleNodeAdded(TurtleNodePresenter *new_node) override
	{
		FuGenPipelineNode *NewNode = PipelineEditor->AddNode(10,10);
		NewNode->SetModel(new_node);
	}
	//
	virtual void HypergraphNodeAdded(HypergraphNodePresenter *new_node) override
	{
		FuGenPipelineNode *NewNode = PipelineEditor->AddNode(10,10);
		NewNode->SetModel(new_node);
	}
	//
	virtual void MeshNodeAdded(MeshNodePresenter *new_node) override
	{
		FuGenPipelineNode *NewNode = PipelineEditor->AddNode(10,10);
		NewNode->SetModel(new_node);
	}
	//
	PipelineEditorListener(FuGenPipelineEditor *pipeline_editor)
		:PipelineEditor(pipeline_editor)
	{}
	//
	virtual ~PipelineEditorListener() override
	{}
};

class NodeEditorAndPipelineTest : public QMainWindow
{
    Q_OBJECT
private:
	FuGenNodeEditor *TestNodeEditor;
	FuGenPipelineEditor *PipelineEditor;
	//
	PipelineEditorListener *TestEditorListener;
	PipelinePresenter *TestPresenter;
	//
public:
	//
	void Test()
	{
		TestEditorListener = new PipelineEditorListener(PipelineEditor);
		//
		TestPresenter = new PipelinePresenter(nullptr);
		TestPresenter->AddListener(TestNodeEditor);
		TestPresenter->AddListener(TestEditorListener);
		//
		TestPresenter->AddTurtleNode();
		TestPresenter->AddHypergraphNode();
		TestPresenter->AddMeshNode();
	}
	//
	NodeEditorAndPipelineTest();
	virtual ~NodeEditorAndPipelineTest() override;
	/*
	 * End of class
	 */
};

#endif // NODE_EDITOR_AND_PIPELINE_TEST_H
