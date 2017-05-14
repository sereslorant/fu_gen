#ifndef GLVIEWTEST_H
#define GLVIEWTEST_H

#include <Presenter/Data/TreeSkeletonPresenter.h>
#include <Presenter/Data/TreeHypergraphPresenter.h>
#include <Presenter/Data/TreeMeshPresenter.h>

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
		virtual void OnInitialization() override
		{
			ViewTest.TestView();
		}
		//
		virtual void OnDraw() override
		{}
		//
		GLViewListener(GLViewTest &view_test)
			:ViewTest(view_test)
		{}
		//
		virtual ~GLViewListener()
		{}
		/*
		 * End of class
		 */
	};
	//
	TreeNode *TestSkeleton = nullptr;
	TreeSkeletonPresenter TestSkeletonPresenter;
	//
	TreeHypergraph TestHypergraph;
	TreeHypergraphPresenter TestHypergraphPresenter;
    //
	MultiMesh *TestMesh;
	TreeMeshPresenter TestMeshPresenter;
	//
	FuGenGLView *GLView;
	//
	GLViewListener ViewListener;
    //
    bool ShowSplines = true;
    bool ShowCylinders = true;
	//
	void CreateTestSkeleton();
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
			GLView->GetEdgeVisualizer().ChooseSkeleton();
			GLView->GetEdgeVisualizer().GetSkeletonRenderer().SetDrawable(&(TestSkeletonPresenter.GetDrawableList()));
			GLView->update();
		}
		//
		if(key_event->key() == Qt::Key_2)
		{
			GLView->GetEdgeVisualizer().ChooseHypergraph();
			GLView->GetEdgeVisualizer().GetHypergraphRenderer().SetDrawable(&(TestHypergraphPresenter.GetDrawableList()));
			GLView->update();
		}
		//
		if(key_event->key() == Qt::Key_3)
		{
			GLView->GetEdgeVisualizer().ChooseMesh();
			GLView->GetEdgeVisualizer().GetMeshRenderer().SetDrawable(&(TestMeshPresenter.GetDrawableList()));
			GLView->update();
		}
		//
		if(key_event->key() == Qt::Key_Q)
		{
            ShowSplines = !ShowSplines;
			GLView->GetEdgeVisualizer().SetShowSplines(ShowSplines);
			GLView->update();
		}
		//
		if(key_event->key() == Qt::Key_W)
		{
            ShowCylinders = !ShowCylinders;
			GLView->GetEdgeVisualizer().SetShowCylinders(ShowCylinders);
			GLView->update();
		}
	}
	//
public:
	//
	void TestView()
	{
		CreateTestSkeleton();
		//
		TestSkeletonPresenter.SetShaderProgram(&GLView->GetEdgeVisualizer().GetSkeletonShaderProgram());
		TestSkeletonPresenter.OnChanged(TestSkeleton);
		//
		CreateTestHypergraph();
		//
		TestHypergraphPresenter.SetShaderProgram(&GLView->GetEdgeVisualizer().GetHypergraphShaderProgram());
		TestHypergraphPresenter.OnChanged(&TestHypergraph);
		//
		CreateTestMesh();
		//
		TestMeshPresenter.SetShaderProgram(&GLView->GetEdgeVisualizer().GetMeshShaderProgram());
		TestMeshPresenter.OnChanged(TestMesh);
	}
	//
	GLViewTest();
	virtual ~GLViewTest() override;
	/*
	 * End of class
	 */
};

#endif // GLVIEWTEST_H
