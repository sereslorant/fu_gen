#ifndef GL_EDGE_VISUALIZER_H
#define GL_EDGE_VISUALIZER_H

#include "GLExt.h"

#include "HypergraphRenderer/GLHypergraphRenderer.h"

class GLEdgeVisualizer
{
private:
	//
	/*
	 * Hypergraph shaders
	 */
	GLuint VertexShader;
	GLuint GSHermite;
	GLuint CatmullRomShader;
	GLuint CylinderShader;
	GLuint FragmentShader;
	//
	/*
	 * MultiMesh shaders
	 */
	GLuint MeshVertexShader;
	GLuint MeshFragmentShader;
	//
	GLHypergraphRenderer *HypergraphRenderer;
	GLRenderer *MeshRenderer;
	//
	enum VisualizerState
	{
		SHOW_HYPERGRAPH,
		SHOW_MESH,
	};
	//
	VisualizerState State = SHOW_MESH;
	//
public:
	//
	void ChooseHypergraph()
	{
		State = SHOW_HYPERGRAPH;
	}
	//
	void ChooseMesh()
	{
		State = SHOW_MESH;
	}
	//
	GLHypergraphRenderer &GetHypergraphRenderer()
	{
		return *HypergraphRenderer;
	}
	//
	IGLShaderProgram &GetMeshShaderProgram()
	{
		return *MeshRenderer;
	}
	//
	IGLRenderer &GetMeshRenderer()
	{
		return *MeshRenderer;
	}
	//
	void Initialize();
	//
	void Resize(int width,int height)
	{
		glViewport(0,0,width,height);
	}
	//
	void Draw();
	//
	GLEdgeVisualizer()
	{}
	//
	~GLEdgeVisualizer()
	{
		delete HypergraphRenderer;
		delete MeshRenderer;
		//
		glDeleteShader(VertexShader);
		glDeleteShader(GSHermite);
		glDeleteShader(CatmullRomShader);
		glDeleteShader(CylinderShader);
		glDeleteShader(FragmentShader);
		glDeleteShader(MeshVertexShader);
	}
	/*
	 * End of class
	 */
};

extern const char *VertexShaderSource;
extern const char *GSHermiteHelper;
extern const char *CatmullRomSource;
extern const char *GenCylinderSource;
extern const char *MeshVertexShaderSource;
extern const char *FragmentShaderSource;

GLuint CompileShader(const char *shader_source,GLenum shader_type);

#endif // GL_EDGE_VISUALIZER_H
