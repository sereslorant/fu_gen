#ifndef TREE_DATA_LISTENER_H
#define TREE_DATA_LISTENER_H

#include <View/EdgeVisualizer/FuGenGLView.h>

#include "Data/TreeDataPresenter.h"

class ViewRefresher : public ITreeDataListener
{
private:
	FuGenGLView *GLView;
	//
public:
	//
	virtual void OnChanged() override
	{
		if(GLView != nullptr)
		{
			GLView->update();
		}
	}
	//
	void SetView(FuGenGLView *gl_view)
	{
		GLView = gl_view;
	}
	//
	ViewRefresher()
	{}
	//
	virtual ~ViewRefresher() override
	{}
};

#endif // TREE_DATA_LISTENER_H

