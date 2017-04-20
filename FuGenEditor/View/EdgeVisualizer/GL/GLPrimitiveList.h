#ifndef GL_DRAWABLE_H
#define GL_DRAWABLE_H

#include <QtGui/QOpenGLContext>

#include <glmath.hpp>

#include "GLExt.h"
#include "IGLRenderer.h"

template<class GLInputFormatStrategy_T>
class GLPrimitiveList : public IGLDrawable
{
protected:
	unsigned int NumVertices;
	GLuint VBO;
	GLuint VAO;
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const = 0;
	//
public:
	//
	void Draw(IGLShaderProgram &renderer) const
	{
		glBindVertexArray(VAO);
		DrawCall(renderer);
		glBindVertexArray(0);
	}
	//
	void Fill(void *vertex_array,unsigned int num_vertices,unsigned int sizeof_data)
	{
		NumVertices = num_vertices;
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		//
		glBufferData(GL_ARRAY_BUFFER,num_vertices * sizeof_data,vertex_array,GL_STATIC_DRAW);
		//
		glBindBuffer(GL_ARRAY_BUFFER,0);
	}
	//
	GLPrimitiveList(void *vertex_array,unsigned int num_vertices,IGLShaderProgram &renderer)
		:NumVertices(num_vertices)
	{
		glGenBuffers(1,&VBO);
		Fill(vertex_array,num_vertices,sizeof(vec4));
		//
		glGenVertexArrays(1,&VAO);
		glBindVertexArray(VAO);
		//
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		GLInputFormatStrategy_T::SetShaderInputFormat(renderer);
		glBindVertexArray(0);
	}
	//
	virtual ~GLPrimitiveList()
	{
		glDeleteBuffers(1,&VBO);
		glDeleteVertexArrays(1,&VAO);
	}
};

#endif // GL_DRAWABLE_H
