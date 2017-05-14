#ifndef FUGENGLVIEW_H
#define FUGENGLVIEW_H


#include "GL/GLEdgeVisualizer.h"

#include <QtWidgets/QOpenGLWidget>

class IGLViewListener
{
public:
	virtual void OnInitialization() = 0;
	//
	virtual void OnDraw() = 0;
	//
	IGLViewListener()
	{}
	//
	virtual ~IGLViewListener()
	{}
	/*
	 * End of class
	 */
};

class FuGenGLView : public QOpenGLWidget
{
    Q_OBJECT
    //
private:
	int width;
	int height;
	//
	GLEdgeVisualizer EdgeVisualizer;
	//
	std::list<IGLViewListener *> Listeners;
	//
protected:
	//
	virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
	//
public:
	//
	void AddListener(IGLViewListener *listener)
	{
		Listeners.push_back(listener);
	}
	//
	GLEdgeVisualizer &GetEdgeVisualizer()
	{
		return EdgeVisualizer;
	}
	//
	virtual QSize minimumSizeHint() const override
	{
		return QSize(50,50);
	}
	//
	virtual QSize sizeHint() const override
	{
		return QSize(250,250);
	}
	//
	FuGenGLView(QWidget *parent = nullptr);
	virtual ~FuGenGLView() override;
	/*
	 * End of class
	 */
};

#endif // FUGENGLVIEW_H
