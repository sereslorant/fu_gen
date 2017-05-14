#ifndef GL_TRIANGLE_LIST_H
#define GL_TRIANGLE_LIST_H

#include "../GLPrimitiveList.h"

class GLTriangleInputFormatStrategy
{
public:
	static void SetShaderInputFormat(IGLShaderProgram &renderer)
	{
		glEnableVertexAttribArray(renderer.GetAttribLocation("Position"));
		glVertexAttribPointer(renderer.GetAttribLocation("Position"),3,GL_FLOAT,GL_FALSE,sizeof(vec4),nullptr);
	}
};

class GLTriangleList : public GLPrimitiveList<GLTriangleInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const override
	{
		glDrawArrays(GL_TRIANGLES,0,NumVertices);
	}
	//
public:
	//
	GLTriangleList(vec4 vertex_array[],unsigned int num_triangles,IGLShaderProgram &renderer)
		:GLPrimitiveList(vertex_array,num_triangles * 3,sizeof(vec4),renderer)
	{
		//
	}
	//
	virtual ~GLTriangleList() override
	{
		//
	}
};

#endif // GL_TRIANGLE_LIST_H
