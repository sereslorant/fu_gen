#ifndef GL_DRAWABLE_H
#define GL_DRAWABLE_H

#include <QtGui/QOpenGLContext>

#include <glmath.hpp>


extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;

extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

template<class GLInputFormatStrategy_T>
class GLPrimitiveList
{
protected:
	unsigned int NumVertices;
	GLuint VBO;
	GLuint VAO;
	//
	virtual void DrawCall() const = 0;
	//
public:
	//
	void Draw()
	{
		glBindVertexArray(VAO);
		DrawCall();
	}
	//
	GLPrimitiveList(vec4 vertex_array[],unsigned int num_vertices,GLuint program)
		:NumVertices(num_vertices)
	{
		glGenBuffers(1,&VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		//
		glBufferData(GL_ARRAY_BUFFER,num_vertices * sizeof(vec4),vertex_array,GL_STATIC_DRAW);
		//
		glGenVertexArrays(1,&VAO);
		glBindVertexArray(VAO);
		//
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		GLInputFormatStrategy_T::SetShaderInputFormat(program);
	}
	//
	virtual ~GLPrimitiveList()
	{
		glDeleteBuffers(1,&VBO);
		glDeleteVertexArrays(1,&VAO);
	}
};

constexpr unsigned int NUM_COMPONENTS = 2;

class GLTriangleInputFormatStrategy
{
public:
	static void SetShaderInputFormat(GLuint program)
	{
		glEnableVertexAttribArray(glGetAttribLocation(program,"Position"));
		glVertexAttribPointer(glGetAttribLocation(program,"Position"),NUM_COMPONENTS,GL_FLOAT,GL_FALSE,sizeof(vec4),nullptr);
	}
};

class GLTriangleList : public GLPrimitiveList<GLTriangleInputFormatStrategy>
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

class GLLineStrip : public GLPrimitiveList<GLTriangleInputFormatStrategy>
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

#endif // GL_DRAWABLE_H
