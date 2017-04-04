#ifndef FUGENGLVIEW_H
#define FUGENGLVIEW_H

#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLContext>

#include "GLDrawable.h"

class FuGenGLView : public QOpenGLWidget
{
    Q_OBJECT
    //
private:
	int width;
	int height;
	//
	GLuint VertexShader;
	GLuint FragmentShader;
	//
	GLuint Program;
	//
	//GLuint VAO;
	//GLuint VBO;
	GLTriangleList *TriangleList;
	GLLineStrip	*LineStrip;
	//
protected:
	//
	virtual void initializeGL() override;
    virtual void resizeGL(int width, int height) override;
    virtual void paintGL() override;
public:
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
