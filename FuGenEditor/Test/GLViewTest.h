#ifndef GLVIEWTEST_H
#define GLVIEWTEST_H

#include <Data/TreeSkeleton.h>

#include <Presenter/TreeHypergraphPresenter.h>
#include <Presenter/TreeMeshPresenter.h>

#include <View/EdgeVisualizer/FuGenGLView.h>

#include <QtWidgets/QMainWindow>
#include <QKeyEvent>

class GLViewTest : public QMainWindow
{
    Q_OBJECT
private:
	//
	class GLViewListener : public IGLViewListener
	{
	private:
		GLViewTest &ViewTest;
	public:
		virtual void OnInitialization()
		{
			ViewTest.TestView();
		}
		//
		GLViewListener(GLViewTest &view_test)
			:ViewTest(view_test)
		{}
		virtual ~GLViewListener()
		{}
		/*
		 * End of class
		 */
	};
	//
	TreeNode *TestGraph = nullptr;;
	TreeHypergraph TestHypergraph;
	MultiMesh TestMesh;
	//
	TreeHypergraphPresenter TestHypergraphPresenter;
	TreeMeshPresenter TestMeshPresenter;
	//
	FuGenGLView *GLView;
	//
	GLViewListener ViewListener;
	//
	void CreateTestGraph()
	{
		//
	}
	//
	void CreateTestHypergraph();
	//
	void CreateTestMesh();
	//
protected:
	//
	virtual void keyPressEvent(QKeyEvent *key_event) override
	{
		QMainWindow::keyPressEvent(key_event);
		//
		if(key_event->key() == Qt::Key_1)
		{
			//std::cout << "TODO" << std::endl;
		}
		//
		if(key_event->key() == Qt::Key_2)
		{
			GLView->GetEdgeVisualizer().ChooseHypergraph();
			update();
		}
		//
		if(key_event->key() == Qt::Key_3)
		{
			GLView->GetEdgeVisualizer().ChooseMesh();
			update();
		}
		//
		if(key_event->key() == Qt::Key_Q)
		{
			GLView->GetEdgeVisualizer().GetHypergraphRenderer().SwitchSplines();
			update();
		}
		//
		if(key_event->key() == Qt::Key_W)
		{
			GLView->GetEdgeVisualizer().GetHypergraphRenderer().SwitchClyinders();
			update();
		}
	}
	//
public:
	//
	void TestView()
	{
		CreateTestHypergraph();
		//
		TestHypergraphPresenter.SetPrimitiveRenderer(&GLView->GetEdgeVisualizer().GetHypergraphRenderer(),&GLView->GetEdgeVisualizer().GetHypergraphRenderer().GetCatmullRomRenderer());
		TestHypergraphPresenter.OnChanged(&TestHypergraph);
		//
		CreateTestMesh();
		//
		TestMeshPresenter.SetMeshRenderer(&GLView->GetEdgeVisualizer().GetMeshRenderer(),&GLView->GetEdgeVisualizer().GetMeshShaderProgram());
		TestMeshPresenter.OnChanged(&TestMesh);
	}
	//
	GLViewTest();
	virtual ~GLViewTest() override;
	/*
	 * End of class
	 */
};

#endif // GLVIEWTEST_H
