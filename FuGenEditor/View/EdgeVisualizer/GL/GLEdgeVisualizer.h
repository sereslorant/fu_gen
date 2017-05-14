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
	GLRenderer *SkeletonRenderer;
	GLHypergraphRenderer *HypergraphRenderer;
	GLRenderer *MeshRenderer;
	//
	enum VisualizerState
	{
		SHOW_SKELETON,
		SHOW_HYPERGRAPH,
		SHOW_MESH,
	};
	//
	IGLRenderer *CurrentRenderer = nullptr;
	//
public:
	//
	void ChooseSkeleton()
	{
		std::cout << "Skeleton chosen" << std::endl;
		//State = SHOW_SKELETON;
		CurrentRenderer = SkeletonRenderer;
	}
	//
	void ChooseHypergraph()
	{
		std::cout << "Hypergraph chosen" << std::endl;
		//State = SHOW_HYPERGRAPH;
		CurrentRenderer = HypergraphRenderer;
	}
	//
	void ChooseMesh()
	{
		std::cout << "Mesh chosen" << std::endl;
		//State = SHOW_MESH;
		CurrentRenderer = MeshRenderer;
	}
	//
	void SetShowSplines(bool show_splines)
    {
        HypergraphRenderer->SetShowSplines(show_splines);
    }
	//
	void SetShowCylinders(bool show_cylinders)
    {
        HypergraphRenderer->SetShowCylinders(show_cylinders);
    }
	//
	IGLShaderProgram &GetSkeletonShaderProgram()
	{
		return *SkeletonRenderer;
	}
	//
	IGLRenderer &GetSkeletonRenderer()
	{
		return *SkeletonRenderer;
	}
	//
	IGLShaderProgram &GetHypergraphShaderProgram()
	{
		return HypergraphRenderer->GetCatmullRomRenderer();
	}
	//
	IGLRenderer &GetHypergraphRenderer()
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
		delete SkeletonRenderer;
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
