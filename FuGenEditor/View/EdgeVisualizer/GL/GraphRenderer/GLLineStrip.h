#ifndef GL_LINE_STRIP_H
#define GL_LINE_STRIP_H

#include "../GLPrimitiveList.h"

class GLSimpleInputFormatStrategy
{
public:
	static void SetShaderInputFormat(GLuint program)
	{
		glEnableVertexAttribArray(glGetAttribLocation(program,"Position"));
		glVertexAttribPointer(glGetAttribLocation(program,"Position"),3,GL_FLOAT,GL_FALSE,sizeof(vec4),nullptr);
	}
};

class GLTriangleList : public GLPrimitiveList<GLSimpleInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall() const override
	{
		glDrawArrays(GL_TRIANGLES,0,NumVertices);
	}
	//
public:
	//
	GLTriangleList(vec4 vertex_array[],unsigned int num_triangles,GLuint program)
		:GLPrimitiveList(vertex_array,num_triangles * 3,program)
	{
		//
	}
	//
	virtual ~GLTriangleList() override
	{}
};

class GLLineStrip : public GLPrimitiveList<GLSimpleInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall() const override
	{
		glDrawArrays(GL_LINE_STRIP,0,NumVertices);
	}
	//
public:
	//
	GLLineStrip(vec4 vertex_array[],unsigned int num_vertices,GLuint program)
		:GLPrimitiveList(vertex_array,num_vertices,program)
	{
		//
	}
	//
	virtual ~GLLineStrip() override
	{}
};

#endif // 
