#ifndef GL_LINE_STRIP_H
#define GL_LINE_STRIP_H

#include "../GLPrimitiveList.h"

class GLSimpleInputFormatStrategy
{
public:
	static void SetShaderInputFormat(IGLShaderProgram &renderer)
	{
		glEnableVertexAttribArray(renderer.GetAttribLocation("Position"));
		glVertexAttribPointer(renderer.GetAttribLocation("Position"),3,GL_FLOAT,GL_FALSE,sizeof(vec4),nullptr);
	}
};

class GLTriangleFan : public GLPrimitiveList<GLSimpleInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const override
	{
		glDrawArrays(GL_TRIANGLE_FAN,0,NumVertices);
	}
	//
public:
	//
	GLTriangleFan(void *vertex_array,unsigned int num_vertices,IGLShaderProgram &program)
		:GLPrimitiveList(vertex_array,num_vertices,sizeof(vec4),program)
	{
		//
	}
	//
	virtual ~GLTriangleFan() override
	{}
};

class GLLineList : public GLPrimitiveList<GLSimpleInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const override
	{
		glDrawArrays(GL_LINES,0,NumVertices);
	}
	//
public:
	//
	GLLineList(void *vertex_array,unsigned int num_vertices,IGLShaderProgram &program)
		:GLPrimitiveList(vertex_array,num_vertices,sizeof(vec4),program)
	{
		//
	}
	//
	virtual ~GLLineList() override
	{}
};

#endif // 
