#ifndef GL_HYPERGRAPH_RENDERER_H
#define GL_HYPERGRAPH_RENDERER_H

#include "../GLExt.h"
#include "../GLRenderer.h"

#include "GLCatmullRom.h"

class GLGeneralizedCylinder : public GLCatmullRom
{
private:
	float BeginTime;
	float EndTime;
	//
	float Radius;
	//
protected:
	//
	virtual void DrawCall(IGLShaderProgram &renderer) const override
	{
		GLint BeginTimeLocation = renderer.GetUniformLocation("BeginTime");
		glUniform1f(BeginTimeLocation,BeginTime);
		//
		GLint EndTimeLocation = renderer.GetUniformLocation("EndTime");
		glUniform1f(EndTimeLocation,EndTime);
		//
		GLint RadiusLocation = renderer.GetUniformLocation("Radius");
		glUniform1f(RadiusLocation,Radius);
		//
		GLCatmullRom::DrawCall(renderer);
	}
	//
public:
	//
	void SetParams(float begin_time,float end_time,float radius)
	{
		BeginTime = begin_time;
		EndTime = end_time;
		//
		Radius = radius;
	}
	//
	GLGeneralizedCylinder(void *vertex_array,unsigned int num_vertices,IGLShaderProgram &renderer)
		:GLCatmullRom(vertex_array,num_vertices,renderer)
	{}
	//
	virtual ~GLGeneralizedCylinder() override
	{}
	/*
	 * End of class
	 */
};

class GLHypergraphRenderer : public IGLRenderer
{
private:
	GLRenderer CatmullRomRenderer;
	GLRenderer CylinderRenderer;
	//
	bool ShowSplines = true;
	bool ShowClyinders = true;
	//
public:
	//
	GLRenderer &GetCatmullRomRenderer()
	{
		return CatmullRomRenderer;
	}
	//
	void SetShowSplines(bool show_splines)
	{
		ShowSplines = show_splines;
	}
	//
	void SetShowCylinders(bool show_cylinders)
	{
		ShowClyinders = show_cylinders;
	}
	//
	virtual void SetDrawable(IGLDrawable *drawable) override
	{
		CatmullRomRenderer.SetDrawable(drawable);
		CylinderRenderer.SetDrawable(drawable);
	}
	//
	virtual void Draw() override
	{
		std::cout << "BeforeSplines: " << glGetError() << std::endl;
		if(ShowSplines)
		{
			CatmullRomRenderer.Draw();
		}
		std::cout << "BeforeCylinders: " << glGetError() << std::endl;
		//
		if(ShowClyinders)
		{
			CylinderRenderer.Draw();
		}
		std::cout << "AfterCylinders: " << glGetError() << std::endl;
	}
	//
	GLHypergraphRenderer(GLuint catmull_rom_shader[],unsigned int catmull_rom_count
						 ,GLuint cylinder_shader[],unsigned int cylinder_count)
		:CatmullRomRenderer(catmull_rom_shader,catmull_rom_count),
		 CylinderRenderer(cylinder_shader,cylinder_count)
	{
		//
	}
	//
	~GLHypergraphRenderer()
	{
		//
	}
};

#endif // GL_HYPERGRAPH_RENDERER_H
