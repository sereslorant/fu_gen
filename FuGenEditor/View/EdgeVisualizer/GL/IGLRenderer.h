#ifndef IGL_RENDERER_H
#define IGL_RENDERER_H

#include <QtGui/QOpenGLContext>

class IGLShaderProgram
{
public:	
	//
	virtual GLint GetAttribLocation(const std::string &attrib_name) = 0;
	//
	virtual GLint GetUniformLocation(const std::string &uniform_name) = 0;
	//
	IGLShaderProgram()
	{}
	//
	virtual ~IGLShaderProgram()
	{}
	/*
	 * End of class
	 */
};

class IGLDrawable
{
public:
	//
	virtual void Draw(IGLShaderProgram &renderer) const = 0;
	//
	IGLDrawable()
	{}
	//
	virtual ~IGLDrawable()
	{}
	/*
	 * End of class
	 */
};

class IGLRenderer
{
public:
	//
	virtual void SetDrawable(IGLDrawable *drawable) = 0;
	//
	virtual void Draw() = 0;
	//
	IGLRenderer()
	{}
	//
	virtual ~IGLRenderer()
	{}
	/*
	 * End of class
	 */
};

class IGLDrawableList : public IGLDrawable
{
public:
	//
	virtual void Clear() = 0;
	//
	virtual void Add(const IGLDrawable *new_drawable) = 0;
	//
	virtual void Remove(const IGLDrawable *removable_drawable) = 0;
	//
	IGLDrawableList()
	{}
	//
	virtual ~IGLDrawableList()
	{}
	/*
	 * End of class;
	 */
};

#endif // IGL_RENDERER_H
