
#include "FuGenGLView.h"

void FuGenGLView::initializeGL()
{
	InitGL(context());
	//
	EdgeVisualizer.Initialize();
	//
	if(Listener != nullptr)
	{
		Listener->OnInitialization();
	}
}

void FuGenGLView::resizeGL(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	//
	EdgeVisualizer.Resize(newWidth,newHeight);
}

#include <chrono>
#include <iostream>

void FuGenGLView::paintGL()
{
	std::cout << glGetString(GL_VERSION) << std::endl;
	//
	EdgeVisualizer.Draw();
}

FuGenGLView::FuGenGLView(QWidget *parent)
	:QOpenGLWidget(parent)
{
	QSurfaceFormat NewFormat;
	//
	NewFormat.setVersion(3,2);
	NewFormat.setProfile(QSurfaceFormat::CoreProfile);
	//
	setFormat(NewFormat);
}

FuGenGLView::~FuGenGLView()
{
	makeCurrent();
	//
}

#include "FuGenGLView.moc"
