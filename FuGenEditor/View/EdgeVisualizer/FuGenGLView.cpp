
#include "FuGenGLView.h"

void FuGenGLView::initializeGL()
{
	InitGL(context());
	//
	EdgeVisualizer.Initialize();
	//
	for(IGLViewListener *Listener : Listeners)
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
	for(IGLViewListener *Listener : Listeners)
	{
		Listener->OnDraw();
	}
	//
	std::cout << "Before" << glGetError() << std::endl;
	EdgeVisualizer.Draw();
	std::cout << "After: " << glGetError() << std::endl;
}

FuGenGLView::FuGenGLView(QWidget *parent)
	:QOpenGLWidget(parent)
{
	QSurfaceFormat NewFormat;
	//
	NewFormat.setVersion(3,3);
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
