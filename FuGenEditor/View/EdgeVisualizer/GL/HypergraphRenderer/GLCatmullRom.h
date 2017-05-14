#ifndef GL_CATMULL_ROM_H
#define GL_CATMULL_ROM_H

#include "../GLPrimitiveList.h"

struct CR_VertexData
{
	vec4 Position;
	vec4 Velocity;
	float Time;
};

class GLCRInputFormatStrategy
{
public:
	static void SetShaderInputFormat(IGLShaderProgram &renderer)
	{
		glEnableVertexAttribArray(renderer.GetAttribLocation("Position"));
		glVertexAttribPointer(renderer.GetAttribLocation("Position"),3,GL_FLOAT,GL_FALSE,sizeof(CR_VertexData),(void *) 0);
		//
		glEnableVertexAttribArray(renderer.GetAttribLocation("Velocity"));
		glVertexAttribPointer(renderer.GetAttribLocation("Velocity"),3,GL_FLOAT,GL_FALSE,sizeof(CR_VertexData),(void *) (sizeof(vec4)));
		//
		glEnableVertexAttribArray(renderer.GetAttribLocation("Time"));
		glVertexAttribPointer(renderer.GetAttribLocation("Time"),1,GL_FLOAT,GL_FALSE,sizeof(CR_VertexData),(void *) (2*sizeof(vec4)));
	}
};

class GLCatmullRom : public GLPrimitiveList<GLCRInputFormatStrategy>
{
protected:
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const override
	{
		glDrawArrays(GL_LINE_STRIP,0,NumVertices);
	}
	//
public:
	//
	GLCatmullRom(void *vertex_array,unsigned int num_vertices,IGLShaderProgram &renderer)
		:GLPrimitiveList(vertex_array,num_vertices,sizeof(CR_VertexData),renderer)
	{
		//
	}
	//
	virtual ~GLCatmullRom() override
	{}
};

#endif // GL_CATMULL_ROM_H
