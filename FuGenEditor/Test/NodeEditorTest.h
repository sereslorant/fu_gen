#ifndef NODE_EDITOR_TEST_H
#define NODE_EDITOR_TEST_H

#include <QComboBox>
#include <QToolBox>

#include <QMainWindow>

#include <Presenter/PipelinePresenter.h>

#include <View/NodeEditor/TurtleNodeEditor.h>
#include <View/NodeEditor/HypergraphNodeEditor.h>
#include <View/NodeEditor/MeshNodeEditor.h>

#include <iostream>

#include <Presenter/ViewRefresher.h>

#include <Presenter/Elements/Nodes/TurtleNodePresenter.h>
#include <Presenter/Elements/Nodes/HypergraphNodePresenter.h>
#include <Presenter/Elements/Nodes/MeshNodePresenter.h>

class NodeEditorTest : public QMainWindow
{
    Q_OBJECT

private:
	QComboBox *ComboBox;
	QToolBox *ToolBox;
	//
	FuGenGLView *EdgeVisualizer;
	//
	TurtleNodePresenter *TurtleNode;
	HypergraphNodePresenter *HypergraphNode;
	MeshNodePresenter *MeshNode;
	//
	PipelinePresenter *Presenter;
	//
	class GLViewListener : public IGLViewListener
	{
	private:
		NodeEditorTest &NodeTest;
	public:
		virtual void OnInitialization() override
		{
			NodeTest.Setup();
		}
		//
		virtual void OnDraw() override
		{}
		//
		GLViewListener(NodeEditorTest &node_test)
			:NodeTest(node_test)
		{}
		//
		virtual ~GLViewListener()
		{}
		/*
		 * End of class
		 */
	};
	//
	GLViewListener ViewListener;
	//
	void Setup()
	{
		Presenter = new PipelinePresenter(EdgeVisualizer);
		//
		TurtleNode = Presenter->AddTurtleNode();
		TurtleNode->SetAxiom("A");
		//
		constexpr double PI = 3.14159265359;
        TurtleNode->SetDeltaAngle(PI/2.0*0.25);
        TurtleNode->SetDeltaDistance(1.0);
		//
		TurtleNode->AddProduction('A',"[&FL!A]/////’[&FL!A]///////’[&FL!A]");
        TurtleNode->AddProduction('F',"S ///// F");
        TurtleNode->AddProduction('S',"F L");
        TurtleNode->AddProduction('L',"[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]");
		//
		TurtleNode->SetRecursionDepth(3);
		//
		HypergraphNode = Presenter->AddHypergraphNode();
		HypergraphNode->SetRadius(0.125);
		HypergraphNode->SetRadiusDecay(0.75);
		HypergraphNode->SetParentWeight(0.0);
		HypergraphNode->SetInitSpeed(0.0);
		HypergraphNode->SetEndSpeed(0.0);
		HypergraphNode->ConnectInput(TurtleNode->GetDataPresenter());
		//
		MeshNode = Presenter->AddMeshNode();
		MeshNode->SetSegmentWidth(4);
		MeshNode->SetSegmentHeight(10);
		MeshNode->ConnectInput(HypergraphNode->GetDataPresenter());
		//
		ToolBox->addItem(new TurtleNodeEditor(TurtleNode), QStringLiteral("TurtleEditor"));
		ToolBox->addItem(new HypergraphNodeEditor(HypergraphNode), QStringLiteral("HypergraphEditor"));
		ToolBox->addItem(new MeshNodeEditor(MeshNode), QStringLiteral("MeshEditor"));
	}
    //
private slots:
	//
	void ComboBoxChanged()
	{
		if(ComboBox->currentText() == "TreeSkeleton")
		{
			Presenter->GetVisualizer().SetCurrentPresenter(&(TurtleNode->GetDataPresenter()));
		}
		if(ComboBox->currentText() == "TreeHypergraph")
		{
			Presenter->GetVisualizer().SetCurrentPresenter(&(HypergraphNode->GetDataPresenter()));
		}
		if(ComboBox->currentText() == "TreeMesh")
		{
			Presenter->GetVisualizer().SetCurrentPresenter(&(MeshNode->GetDataPresenter()));
		}
	}
	//
public:
	//
	NodeEditorTest();
	//
	virtual ~NodeEditorTest() override;
};

#endif // NODE_EDITOR_TEST_H
