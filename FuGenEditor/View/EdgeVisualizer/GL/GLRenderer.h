#ifndef GL_RENDERER_H
#define GL_RENDERER_H

#include "GLExt.h"
#include "IGLRenderer.h"

//#include <iostream>

class GLRenderer : public IGLShaderProgram, public IGLRenderer
{
protected:
	GLuint Program;
	//
	IGLDrawable *Drawable = nullptr;
	//
public:
	//
	virtual GLint GetAttribLocation(const std::string &attrib_name) override
	{
		return glGetAttribLocation(Program,attrib_name.c_str());
	}
	//
	virtual GLint GetUniformLocation(const std::string &uniform_name) override
	{
		return glGetUniformLocation(Program,uniform_name.c_str());
	}
	//
	virtual void SetDrawable(IGLDrawable *drawable) override
	{
		//std::cout << "New drawable: " << drawable << std::endl;
		Drawable = drawable;
	}
	//
	virtual void Draw() override
	{
		if(Drawable != nullptr)
		{
			glUseProgram(Program);
			//
			Drawable->Draw(*this);
			//
			glUseProgram(0);
		}
	}
	//
	GLRenderer(GLuint linked_shaders[],unsigned int num_linked_shaders)
	{
		Program = glCreateProgram();
		//
		for(unsigned int i=0;i < num_linked_shaders;i++)
		{
			glAttachShader(Program,linked_shaders[i]);
		}
		//
		glLinkProgram(Program);
		//
		for(unsigned int i=0;i < num_linked_shaders;i++)
		{
			glDetachShader(Program,linked_shaders[i]);
		}
	}
	//
	virtual ~GLRenderer()
	{
		glUseProgram(0);
		glDeleteProgram(Program);
	}
	/*
	 * End of class
	 */
};

#endif // GL_RENDERER_H
