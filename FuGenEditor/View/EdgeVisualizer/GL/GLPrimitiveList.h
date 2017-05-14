#ifndef GL_DRAWABLE_H
#define GL_DRAWABLE_H

#include <QtGui/QOpenGLContext>

#include <glmath.hpp>

#include "GLExt.h"
#include "IGLRenderer.h"

#include <iostream>

template<class GLInputFormatStrategy_T>
class GLPrimitiveList : public IGLDrawable
{
private:
	GLuint VBO;
	GLuint VAO;
	//
protected:
	unsigned int NumVertices;
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const = 0;
	//
public:
	//
	void Draw(IGLShaderProgram &renderer) const
	{
		std::cout << this << std::endl;
		std::cout << VAO << std::endl;
		std::cout << "Before bind vao: " << glGetError() << std::endl;
		glBindVertexArray(VAO);
		//
		std::cout << "Before draw call: " << glGetError() << std::endl;
		DrawCall(renderer);
		std::cout << "After draw call: " << glGetError() << std::endl;
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
	GLPrimitiveList(void *vertex_array,unsigned int num_vertices,unsigned int struct_size,IGLShaderProgram &renderer)
		:NumVertices(0)
	{
		std::cout << this << std::endl;
		std::cout << "Before gen vao: " << glGetError() << std::endl;
		glGenVertexArrays(1,&VAO);
		std::cout << VAO << std::endl;
		std::cout << "Before bind vao: " << glGetError() << std::endl;
		glBindVertexArray(VAO);
		std::cout << "After gen vao: " << glGetError() << std::endl;
		//
		glGenBuffers(1,&VBO);
		std::cout << "After gen vbo: " << glGetError() << std::endl;
		//
		std::cout << "Before bind vbo: " << glGetError() << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		std::cout << "Before set format: " << glGetError() << std::endl;
		GLInputFormatStrategy_T::SetShaderInputFormat(renderer);
		std::cout << "Before bind vao: " << glGetError() << std::endl;
		glBindVertexArray(0);
		std::cout << "After bind vao: " << glGetError() << std::endl;
	}
	//
	virtual ~GLPrimitiveList()
	{
		std::cout << "Deleting" << std::endl;
		glDeleteBuffers(1,&VBO);
		glDeleteVertexArrays(1,&VAO);
	}
};

#endif // GL_DRAWABLE_H
