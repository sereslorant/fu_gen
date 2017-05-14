#ifndef PIPELINE_VISUALIZATION_TEST_H
#define PIPELINE_VISUALIZATION_TEST_H

#include <Presenter/PipelinePresenter.h>

#include <Presenter/Elements/Nodes/TurtleNodePresenter.h>
#include <Presenter/Elements/Nodes/HypergraphNodePresenter.h>
#include <Presenter/Elements/Nodes/MeshNodePresenter.h>

#include <Presenter/Elements/EdgePresenter.h>

#include <QtWidgets/QMainWindow>


#include <View/PipelineEditor/FuGenPipelineEditor.h>
#include <View/EdgeVisualizer/FuGenGLView.h>

class PipelineVisualizationTest : public QMainWindow
{
    Q_OBJECT
private:
    FuGenPipelineEditor *PipelineEditor;
    FuGenGLView         *EdgeVisualizer;
	//
    class GLViewListener : public IGLViewListener
	{
	private:
		PipelineVisualizationTest &Test;
	public:
		virtual void OnInitialization() override
		{
			Test.InitTest();
		}
		//
		virtual void OnDraw() override
		{}
		//
		GLViewListener(PipelineVisualizationTest &test)
			:Test(test)
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
    PipelinePresenter *TestPipelinePresenter;
    TurtleNodePresenter *TestNodePresenter1;
    HypergraphNodePresenter *TestNodePresenter2;
    MeshNodePresenter *TestNodePresenter3;
    /*EdgePresenter *TestEdgePresenter1;
    EdgePresenter *TestEdgePresenter2;
    EdgePresenter *TestEdgePresenter3;*/
    //
    void InitTest()
    {
        EdgeVisualizer->GetEdgeVisualizer().SetShowSplines(true);
        EdgeVisualizer->GetEdgeVisualizer().SetShowCylinders(true);
        //
        TestPipelinePresenter = new PipelinePresenter(EdgeVisualizer);
        //
        TestNodePresenter1 = new TurtleNodePresenter(
                                    EdgeVisualizer
                                );
		//
		TestNodePresenter1->SetAxiom("A");
		//
		constexpr double PI = 3.14159265359;
        TestNodePresenter1->SetDeltaAngle(PI/2.0*0.25);
        TestNodePresenter1->SetDeltaDistance(1.0);
		//
		TestNodePresenter1->AddProduction('A',"[&FL!A]/////’[&FL!A]///////’[&FL!A]");
        TestNodePresenter1->AddProduction('F',"S ///// F");
        TestNodePresenter1->AddProduction('S',"F L");
        TestNodePresenter1->AddProduction('L',"[’’’^^{.-f.+f.+f.-|-f.+f.+f.}]");
		//
		TestNodePresenter1->SetRecursionDepth(5);
        //
        TestNodePresenter2 = new HypergraphNodePresenter(
                                    EdgeVisualizer
                                );
		//
		TestNodePresenter2->SetRadius(0.125);
		TestNodePresenter2->SetRadiusDecay(0.75);
		TestNodePresenter2->SetParentWeight(0.0);
		TestNodePresenter2->SetInitSpeed(0.0);
		TestNodePresenter2->SetEndSpeed(0.0);
        //
        TestNodePresenter3 = new MeshNodePresenter(
                                    EdgeVisualizer
                                );
		//
		TestNodePresenter3->SetSegmentWidth(4);
		TestNodePresenter3->SetSegmentHeight(10);
        //
        /*TestEdgePresenter1 = new EdgePresenter(
                                    *TestPipelinePresenter,
                                    TestNodePresenter1->GetDataPresenter()
                                );
        //
        TestEdgePresenter2 = new EdgePresenter(
                                    *TestPipelinePresenter,
                                    TestNodePresenter2->GetDataPresenter()
                                );
        //
        TestEdgePresenter3 = new EdgePresenter(
                                    *TestPipelinePresenter,
                                    TestNodePresenter3->GetDataPresenter()
                                );*/
        //
		std::cout << "N1 to N2 " << TestNodePresenter2->IsConnectable(TestNodePresenter1) << std::endl;
		std::cout << "N2 to N1 " << TestNodePresenter1->IsConnectable(TestNodePresenter2) << std::endl;
		std::cout << "N2 to N3 " << TestNodePresenter3->IsConnectable(TestNodePresenter2) << std::endl;
		std::cout << "N3 to N2 " << TestNodePresenter2->IsConnectable(TestNodePresenter3) << std::endl;
		std::cout << "N1 to N3 " << TestNodePresenter3->IsConnectable(TestNodePresenter1) << std::endl;
		std::cout << "N3 to N1 " << TestNodePresenter1->IsConnectable(TestNodePresenter3) << std::endl;
		//
		TestNodePresenter2->ConnectInput(TestNodePresenter1->GetDataPresenter());
		TestNodePresenter3->ConnectInput(TestNodePresenter2->GetDataPresenter());
		//
		FuGenPipelineNode *First = PipelineEditor->AddNode(10,10);
		First->SetModel(TestNodePresenter1);
		FuGenPipelineNode *Second = PipelineEditor->AddNode(40,80);
		Second->SetModel(TestNodePresenter2);
		FuGenPipelineNode *Third = PipelineEditor->AddNode(50,140);
		Third->SetModel(TestNodePresenter3);
		FuGenPipelineNode *Last = PipelineEditor->AddNode(60,200);
		Last->SetModel(TestPipelinePresenter->AddAppNode());
		//
		/*FuGenPipelineEdge *FirstToSecond = PipelineEditor->AddEdge(First,Second);
		FirstToSecond->SetModel(TestEdgePresenter1);
		//
		FuGenPipelineEdge *SecondToThird = PipelineEditor->AddEdge(Second,Third);
		SecondToThird->SetModel(TestEdgePresenter2);
		//
        FuGenPipelineEdge *ThirdToApp = PipelineEditor->AddEdge(Third,Last);
        ThirdToApp->SetModel(TestEdgePresenter3);*/
		//
		PipelineEditor->SetModel(TestPipelinePresenter);
    }
    //
public:
	//
	PipelineVisualizationTest();
	virtual ~PipelineVisualizationTest() override;
	/*
	 * End of class
	 */
};

#endif // PIPELINE_VISUALIZATION_TEST_H
